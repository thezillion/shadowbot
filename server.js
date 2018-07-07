
const io = require("socket.io"),
      server = io.listen(5000)

let sequenceNumberByClient = new Map()

var clientsDict = {
    "serialClient": null,
    "nodeMCUClient": null
}

// CppClient: TRYHAJcVBh5vKH5EAAAA

// event fired every time a new client connects:
server.on("connection", (socket) => {
    console.info(`Client connected [id=${socket.id}]`)
    // initialize this client's sequence number
    // sequenceNumberByClient.set(socket, 1)

    socket.emit("init", null)
    console.log("Connection");

    socket.on("client-serial-event", function(msg) {
        console.log("Serial client connected")
        clientsDict.serialClient = socket
    })

    socket.on("client-nodeMCU-event", function(msg) {
        console.log("NodeMCU connected")
        clientsDict.nodeMCUClient = socket
    })

    socket.on("data-from-serial", function(data) {
        // console.log(data)
        
        if (clientsDict.nodeMCUClient) {
            try {
                // console.log()
                clientsDict.nodeMCUClient.emit("data-from-server", (JSON.parse(data)))
            } catch (e) {
                // do nothing
            }
            
        }
    })

    // when socket disconnects, remove it from the list:
    socket.on("disconnect", () => {
        // sequenceNumberByClient.delete(socket)
        console.info(`Client gone [id=${socket.id}]`)
    })
})

// // sends each client its current sequence number
// setInterval(() => {
//     for (const [client, sequenceNumber] of sequenceNumberByClient.entries()) {
//         client.emit("seq-num", sequenceNumber)
//         sequenceNumberByClient.set(client, sequenceNumber + 1)
//     }
// }, 1000)