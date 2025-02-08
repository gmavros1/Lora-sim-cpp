import numpy as np
import matplotlib.pyplot as plt

def generate_lora_baseband(payload_bits, SF=7, BW=125e3, Fs=125e3):
    """
    Generate a simple LoRa-like baseband waveform (IQ = complex samples)
    for the given payload bits, spreading factor SF, bandwidth BW,
    and sampling rate Fs.

    This is a *minimal* illustration, not a complete LoRa PHY.
    """
    # Number of symbols is the length of payload_bits (one symbol per 'byte' chunk here
    # for simplicity—LoRa actually uses coding and more complex mapping).
    # We'll assume each bit is mapped to a 'symbol index' in [0..2^SF-1].
    # For simplicity, treat each 8 bits as one symbol index:
    symbols = []
    for i in range(0, len(payload_bits), SF):
        # Take SF bits at a time (or fewer if at the end)
        chunk = payload_bits[i : i+SF]
        symbol_value = int(''.join(str(b) for b in chunk), 2)
        symbols.append(symbol_value)

    # Symbol duration
    T_sym = (2**SF) / BW
    samples_per_symbol = int(T_sym * Fs)

    # Prepare output array
    total_samples = samples_per_symbol * len(symbols)
    baseband = np.zeros(total_samples, dtype=complex)

    # Generate each symbol as an upchirp offset by 'symbol_value'
    # freq(t) = (BW / T_sym) * t + (symbol_value * BW / 2^SF) / T_sym
    # phase(t) = 2*pi * integral of freq(t) dt
    time = np.arange(samples_per_symbol) / Fs

    for idx, sym in enumerate(symbols):
        # Start index for this symbol in the baseband array
        start_idx = idx * samples_per_symbol
        end_idx   = start_idx + samples_per_symbol

        # Symbol-specific frequency offset
        f0 = (sym * BW) / (2**SF)  # offset in Hz
        k  = BW / T_sym            # chirp rate

        # Instantaneous frequency: f(t) = f0 + k*t
        # Phase(t) = 2*pi * ∫f(t) dt = 2*pi*( f0*t + 0.5*k*t^2 )
        phase = 2 * np.pi * ( f0 * time + 0.5 * k * time**2 )
        baseband[start_idx:end_idx] = np.exp(1j * phase)

    return baseband


# -----------------
# Example usage
# -----------------
# Create a simple "payload" of bits. For illustration, let's just do 16 bits:
payload_bits = [1,0,1,0,0,1,1,0,  1,1,1,0,0,0,1,0]

# Generate waveforms for SF7 and SF9 (same bits)
wave_sf7 = generate_lora_baseband(payload_bits, SF=7, BW=125e3, Fs=125e3)
wave_sf9 = generate_lora_baseband(payload_bits, SF=9, BW=125e3, Fs=125e3)

# Plot magnitude (or real part) in time
t_sf7 = np.arange(len(wave_sf7)) / 125e3
t_sf9 = np.arange(len(wave_sf9)) / 125e3

plt.figure(figsize=(10,6))

plt.subplot(2,1,1)
plt.title("LoRa Waveform (SF7)")
plt.plot(t_sf7, np.real(wave_sf7), label='Real part')
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.legend()
plt.grid(True)

plt.subplot(2,1,2)
plt.title("LoRa Waveform (SF9)")
plt.plot(t_sf9, np.real(wave_sf9), color='orange', label='Real part')
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.show()
