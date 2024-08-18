import argparse

def decode_hex_value(hex_value):
    # Convert the hex value to an integer
    value = int(hex_value, 16)

    # Extract the lower 5 bits (node ID)
    node_id = value & 0x1F  # 0x1F is 00011111 in binary

    # Extract the upper 6 bits (packet ID)
    packet_id = (value >> 5) & 0x3F  # 0x3F is 00111111 in binary

    return node_id, packet_id

if __name__ == "__main__":
    # Set up argument parser
    parser = argparse.ArgumentParser(description="Decode a hex value into node ID and packet ID.")
    parser.add_argument("hex_value", help="Hexadecimal value to decode (e.g., 0x1A3)")

    # Parse the arguments
    args = parser.parse_args()

    # Decode the provided hex value
    node_id, packet_id = decode_hex_value(args.hex_value)
    print(f"Node ID: {node_id}, Packet ID: {packet_id}")
