import subprocess
import time

ports = [5001, 5002, 5003]

# Start nodes
processes = [subprocess.Popen(["./bin/kademlia_client", str(port)]) for port in ports]

# Wait for nodes to discover each other
time.sleep(2)

# Check routing tables (assuming your node has an API for querying its state)
for port in ports:
    result = subprocess.run(["curl", f"http://localhost:{port}/routing_table"], capture_output=True, text=True)
    print(f"Node {port} Routing Table:\n", result.stdout)

# Cleanup
for p in processes:
    p.terminate()
