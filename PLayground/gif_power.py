import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

# -------------------------
# 1) Define the scenario
# -------------------------

# Let's simulate a timeline from t=0 to t=10 seconds in 100 steps:
num_points = 100
t = np.linspace(0, 10, num_points)

# We define three states over time:
#  - Sleep:      0 <= t < 3
#  - Listening:  3 <= t < 7
#  - Transmit:   7 <= t <= 10
# We'll assign different "amplitudes" (power) in each region.

power = np.zeros_like(t)

for i, ti in enumerate(t):
    if ti < 3:        # Sleep
        power[i] = 5  # e.g., 5 mW
    elif ti < 7:      # Listening
        power[i] = 30 # e.g., 30 mW
    else:             # Transmit
        power[i] = 100  # e.g., 100 mW

# In reality, you might read these states from your simulator logs
# or define them more precisely. For demonstration, it's piecewise constant.

# -------------------------
# 2) Set up the plot
# -------------------------
fig, ax = plt.subplots(figsize=(6,4))
ax.set_xlim(0, 10)      # time from 0..10
ax.set_ylim(0, 110)     # power up to ~110 mW
ax.set_xlabel("Time (s)")
ax.set_ylabel("Power Consumption (mW)")
ax.set_title("Transceiver Power States Over Time")

(line,) = ax.plot([], [], lw=2, color='blue')

# -------------------------
# 3) Animation function
# -------------------------
def init():
    # Initialize the line object; no data
    line.set_data([], [])
    return (line,)

def update(frame):
    """
    frame: goes from 0 to num_points-1
    We will plot the power from t=0 up to the current frame.
    """
    xdata = t[:frame+1]
    ydata = power[:frame+1]
    line.set_data(xdata, ydata)
    return (line,)

# Create animation (100 frames, 100 ms per frame)
anim = FuncAnimation(
    fig,
    update,
    frames=num_points,
    init_func=init,
    interval=100,   # 100 ms between frames => 10 fps
    blit=True
)

# -------------------------
# 4) Save to GIF
# -------------------------
# IMPORTANT: You must have either ImageMagick or ffmpeg installed.
# E.g., to use ImageMagick:
anim.save("transceiver_power.gif", writer='imagemagick')

# If you prefer ffmpeg:
# anim.save("transceiver_power.gif", writer='ffmpeg')

plt.show()
