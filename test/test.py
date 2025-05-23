import socket
import hashlib
from concurrent.futures import ThreadPoolExecutor

HOST = "localhost"
PORT = 9000

def sha256_hex(msg: str) -> str:
    return hashlib.sha256(msg.encode()).hexdigest()

def send_and_receive(msg: str) -> str:
    with socket.create_connection((HOST, PORT)) as sock:
        sock.sendall((msg + "\n").encode())
        data = b""
        while not data.endswith(b"\n"):
            chunk = sock.recv(4096)
            if not chunk:
                break
            data += chunk
        return data.decode().strip()

def test_simple_cases():
    print("🧪 Running simple tests...")
    for msg in ["hello", "world", "foo", "bar"]:
        expected = sha256_hex(msg)
        actual = send_and_receive(msg)
        assert actual == expected, f"❌ Failed: {msg}"
    print("✅ Simple tests passed.")

def test_large_input():
    print("🧪 Testing large input (10MB)...")
    msg = "x" * (10 * 1024 * 1024)
    expected = sha256_hex(msg)
    actual = send_and_receive(msg)
    assert actual == expected, "❌ Failed on large input"
    print("✅ Large input test passed.")

def test_parallel_requests():
    print("🧪 Testing parallel requests...")
    with ThreadPoolExecutor(max_workers=20) as pool:
        futures = [pool.submit(send_and_receive, f"parallel-{i}") for i in range(50)]
        for i, fut in enumerate(futures):
            result = fut.result()
            expected = sha256_hex(f"parallel-{i}")
            assert result == expected, f"❌ Parallel test failed at {i}"
    print("✅ Parallel tests passed.")

if __name__ == "__main__":
    test_simple_cases()
    test_large_input()
    test_parallel_requests()
    print("🏁 All tests completed successfully.")
