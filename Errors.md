
# 1. `curl: (1) Received HTTP/0.9 when not allowed`

## Why you got this error:

Understanding the version:

    HTTP/0.9 — The earliest version, only supports GET requests and does not include headers or status codes.

    HTTP/1.0 — Introduced headers, status codes, and more functionality.

    HTTP/1.1 — Adds persistent connections, chunked transfer encoding, and more (still widely used).

    HTTP/2.0 — Binary protocol with multiplexing, header compression, etc.

    HTTP/3.0 — Uses QUIC instead of TCP for faster and more reliable delivery.

curl expects a modern HTTP version (like 1.0 or 1.1) that includes headers. But your server replied with HTTP/0.9, which doesn't include the structure curl needs.
How to fix it:

Make sure your C++ web server is generating proper HTTP/1.0 or HTTP/1.1 responses.

A proper HTTP/1.1 response should look like:

`HTTP/1.1 200 OK
Content-Type: text/plain
Content-Length: 14`


Always return the same type in all code paths of your lambda