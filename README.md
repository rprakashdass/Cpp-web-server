<status line>\r\n
<header1: value1>\r\n
<header2: value2>\r\n
...
\r\n
<body>

# Threadpool
## Parallel requests
`curl http://localhost:8080 & curl http://localhost:8080 &`
Simulate curl response using
`for i in {1..50}; do curl -s http://localhost:8080 & done; wait`