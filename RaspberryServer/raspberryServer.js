const udp = require('dgram')
const server = udp.createSocket('udp4')

const port = 2000

server.on('listening', () => {
    const address = server.address()
    console.log('Listening at port ', address.port)
})

server.on('message', (message, info) => {
    console.log('RaspberryPi Server by David Andrino and Fernando Sanz')

    let count = 0
    let aX = [], aY = [], aZ = [], aR = [], aG = [], aB = []

    console.log('Data received at ' + Date().toLocaleString('es-ES'))
    JSON.parse(message).forEach(e => {
        console.log(`\tSample ${e.sample}:\n\t\tAcceleration: (x, y, z)=(${e.acceleration.x}, ${e.acceleration.y}, ${e.acceleration.z})\n\t\tColor: (r, g, b)=(${e.color.r}, ${e.color.g}, ${e.color.b})`)
        aX.push(e.acceleration.x)
        aY.push(e.acceleration.y)
        aZ.push(e.acceleration.z)
        aR.push(e.color.r)
        aG.push(e.color.g)
        aB.push(e.color.b)
    });
     
    let [mX, dX] = calculateParams(aX)
    let [mY, dY] = calculateParams(aY)
    let [mZ, dZ] = calculateParams(aZ)
    let [mR, dR] = calculateParams(aR)
    let [mG, dG] = calculateParams(aG)
    let [mB, dB] = calculateParams(aB)

    console.log(`Average data:\n\t(x, y, z) = (${mX}, ${mY}, ${mZ})\n\t(r, g, b) = (${mR}, ${mG}, ${mB})`) 
    console.log(`Standard dev:\n\t(x, y, z) = (${dX}, ${dY}, ${dZ})\n\t(r, g, b) = (${dR}, ${dG}, ${dB})`) 

    const response = Buffer.from('ACK')
    server.send(response, info.port, info.address, (err) => {})
})

function calculateParams(arr) {
    if (!arr || arr === 0) return [0, 0]

    const n      = arr.length;
    const mean   = arr.reduce((sum, x) => sum + x, 0) / n;
    const stdDev = Math.sqrt(arr.reduce((sum, x) => sum + (x - mean) ** 2, 0) / n);

    return [mean, stdDev];
}

server.bind(port)
