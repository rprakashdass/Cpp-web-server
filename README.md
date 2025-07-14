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



Problems faced:
    -> Gracefull shutdown has'nt worked properly becoz of accept() - a blocking system call and rectified using file control by setting flags that made non-blocking, it is a lightweight alternative to select() and poll()
    
std::this_thread::sleep_for(std::chrono::milliseconds(100));

It simply tells the thread:

    “Pause for 100 milliseconds before trying again.”

This:

    Reduces CPU usage to almost 0 when idle

    Still keeps the server responsive (100ms is short)

    Is a classic way to handle idle loops in non-blocking programs

