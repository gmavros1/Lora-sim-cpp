from functions import *
from protocol import Multihop
from protocol import Lorawan


def join_process(self):
    for nd in self.nodes:
        nd.type = 0

    self.max_sf = 7


def join_process_adr(self):
    for nd in self.nodes:
        nd.type = 0

    sum_sf = 0.0

    gw = self.gateways[0]
    for nd in self.nodes:
        dist = distance_nodes(nd, gw)

        rec_power = calculate_received_power(
            dist, nd.transmission_power)

        # ADR like
        while True:
            if calculate_snr(rec_power, -(130 + 2.5)) >= snr_limit(nd.sf) + 10:
                break
            elif nd.sf == 12:
                # print("OUT OF RANGE")
                break
            else:
                nd.sf += 1

        temp_sf = nd.sf

        sum_sf += temp_sf  # If we want the mean - comment out following

        if temp_sf > self.max_sf:
            self.max_sf = temp_sf

    self.max_sf = float(sum_sf / len(self.nodes))
    ### TO ENABLE MULTIHOP ###
    # print(self.max_sf)


def multihop_join_process_inf(self):
    # Store nodes, first index is type (0 starting from close to gw)
    # store node, rec_power, rec_id
    node_and_types = []

    # 1. Collect L0 - single hop to gw
    node_and_types.append([])
    for node in self.nodes:
        # For each node select the min distance form gw
        distance_to_gw = []
        for gw in self.gateways:
            distance_to_gw.append(distance_nodes(node, gw))
        min_distance = min(distance_to_gw)

        rec_power = calculate_received_power(
            min_distance, node.transmission_power)

        if calculate_snr(rec_power, -(130 + 2.5)) >= snr_limit(node.sf) + 10:  # rec_power >= -130:
            node.type = 0  # middle node - which is also the type index of node_and_types list
            node.state = "Listen"
            node_and_types[-1].append(
                {"node": node, "rec_power": [rec_power], "rec_id": [-1]})  # same index - associate id - rec power

    # 2. Go for the others
    level = 1
    while True:

        node_and_types.append([])

        count_new_entries = 0
        for node in self.nodes:  # node which I want to associate with a relay node
            if node.type != -1: continue  # Only unassigned nodes

            rec_powers = []
            rec_ids = []

            for r_node in self.nodes:
                if (r_node.type != level - 1): continue  # Only level - 1 nodes

                # print("IN")

                distance = distance_nodes(node, r_node)
                # print(distance)
                rec_power = calculate_received_power(distance, node.transmission_power)

                if calculate_snr(rec_power, - (109 + 2.5)) >= snr_limit(node.sf) + 10:  # rec_power >= -109:
                    count_new_entries += 1  # To stop when we have no other nodes
                    rec_powers.append(rec_power)
                    rec_ids.append(r_node.id)
                    node.type = level
                    node.state = "Listen"

            if len(rec_powers) > 0:
                node_and_types[level].append(
                    {"node": node, "rec_power": rec_powers,
                     "rec_id": rec_ids})  # same index - associate id - rec power

        if count_new_entries == 0:
            node_and_types.pop()
            break
        level += 1

    # It is minus one due to last increase
    level -= 1

    self.general_level = level

    # 3. Clustering algorithm preparation
    only_nodes = []
    for level_in_level in node_and_types:
        only_nodes.append([])
        for node in level_in_level:
            only_nodes[-1].append({"node": node["node"]})

    # 4. Build clusters
    for index_level in range(len(only_nodes) - 1):
        only_nodes[index_level + 1], only_nodes[index_level] = build_clusters(self, only_nodes[index_level + 1],
                                                                                   only_nodes[index_level])

    # 5. Define Following Nodes
    for index_level in range(len(only_nodes) - 1):
        for node_type1 in only_nodes[index_level]:
            nd1 = node_type1["node"]
            for node_type0 in only_nodes[index_level + 1]:
                nd0 = node_type0["node"]

                if nd1.id == nd0.assigned_node:
                    nd1.node_following = nd0.id
                    break

    # 6 See if a type 1 node has no assigned type 0 nodes make it type 0
    for node in self.nodes:  # Make them type 0
        if node.node_following is None:
            node.type = level
            node.protocol = Lorawan(None)
            node.state = "Sleep"
        else:
            node.protocol = Multihop()

    # Every node close to gw has assigned node -1
    for node in self.nodes:
        if node.type == 0:
            node.assigned_node = -1


def build_clusters(self, type0_nodes, type1_nodes):
    # print(type1_nodes)

    m = []

    # For every type 1 node
    for type1 in type1_nodes:
        node_1 = type1["node"]
        m.append([])
        for type0 in type0_nodes:
            node_0 = type0["node"]
            m[-1].append(calculate_received_power(distance_nodes(node_1,
                                                                 node_0), node_0.transmission_power))

    def fm(i, p, m):
        return m[i].index(p)

    m_sorted = []

    for i in range(len(m)):
        m_i = m[i].copy()
        m_i.sort()
        m_sorted.append(m_i)
        m_sorted[-1] = [x for x in m_sorted[-1] if x > -109]

    f_m = []
    for i in range(len(m_sorted)):
        f_m.append([])
        for p in m_sorted[i]:
            f_m[-1].append(fm(i, p, m))

    max_priority = self.num_nodes
    already_assigned_nodes = []
    when_type_1_assigned_to_node_added = []

    def indices(mylist, value):
        return [i for i, x in enumerate(mylist) if x == value]

    for i in range(max_priority):
        priority_i = []
        for type1_list in f_m:
            try:
                priority_i.append(type1_list[i])
            except:
                priority_i.append(None)

        # print(priority_i)
        # Start Assigning type 0 to type 1
        type_0_to_be_assigned = list(set(priority_i))
        # print(type_0_to_be_assigned)
        # type_0_to_be_assigned = type_0_to_be_assigned.remove(None)
        # print(type_0_to_be_assigned)

        for element in type_0_to_be_assigned:
            if element in already_assigned_nodes or element is None:
                continue
            if priority_i.count(element) == 1:
                winner = priority_i.index(element)
                type0_nodes[element]["node"].channel = type1_nodes[winner]["node"].channel
                type0_nodes[element]["node"].assigned_node = type1_nodes[winner]["node"].id
                already_assigned_nodes.append(element)
                when_type_1_assigned_to_node_added.append(winner)
            else:
                to_whch_types1 = indices(priority_i, element)
                score = {}
                for nd in to_whch_types1:
                    score[nd] = when_type_1_assigned_to_node_added.count(nd)
                winner = min(score, key=score.get)
                type0_nodes[element]["node"].channel = type1_nodes[winner]["node"].channel
                type0_nodes[element]["node"].assigned_node = type1_nodes[winner]["node"].id
                already_assigned_nodes.append(element)
                when_type_1_assigned_to_node_added.append(winner)

    return type0_nodes, type1_nodes
