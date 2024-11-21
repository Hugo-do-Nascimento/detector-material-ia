let model;
let serialPort;
let writer;
const classNames = ["PAPEL", "PLÁSTICO"];

async function loadModel() {
    model = await tmImage.load(
        "https://teachablemachine.withgoogle.com/models/xXBQgKwIv/model.json", 
        "https://teachablemachine.withgoogle.com/models/xXBQgKwIv/metadata.json"
    )
    console.log("Modelo carregado com sucesso!")
    setupWebcam();
}

async function setupWebcam() {
    const video = document.getElementById("webcam");

    const stream = await navigator.mediaDevices.getUserMedia({ 
        video: true 
    });

    video.srcObject = stream;
    video.play()

    setInterval(() => classifyImage(), 2000);
}

async function classifyImage() {
    if (!model) return;

    const prediction = await model.predict(document.getElementById("webcam"));

    const highestPrediction = prediction.sort((a, b) => b.probability - a.probability)[0];

    console.log(`Material detectado: ${highestPrediction.className} com probabilidade: ${highestPrediction.probability.toFixed(2)}`);
    // sendToAArduino(highestPrediction.className);

    const consoleOutput = document.getElementById('console-output');

    consoleOutput.innerHTML = `
        <p>Material detectado: ${highestPrediction.className}</p>
        <p>Probabilidade :  ${highestPrediction.probability.toFixed(2)}</p>
    `;
}

// document.getElementById("connectButton").addEventListener("click", async () => {
//     try {
//         serialPort = await navigator.serial.requestPort();
//         await serialPort.open({ baudRate: 9600 });
//         writer = serialPort.writable.getWriter();
//         console.log("Conectado ao Arduino!");
//     } catch (error) {
//         console.error("Erro ao conectar ao Arduino: ", error);
//     }
// });

// async function sendToAArduino(material) {
//     if (writer) {
//         const command = `${material}\n`;
//         await writer.write(new TextEncoder().encode(command));
//         console.log(`Comando enviado: ${command}`);
//     }
// }

loadModel();