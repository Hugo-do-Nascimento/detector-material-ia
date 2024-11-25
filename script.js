let model;
let serialPort;
let writer;
const classNames = ["p", "t"];
let isSending = false;  // Para garantir que os comandos não sejam enviados muito rápido

async function loadModel() {
    model = await tmImage.load(
        "https://teachablemachine.withgoogle.com/models/xXBQgKwIv/model.json", 
        "https://teachablemachine.withgoogle.com/models/xXBQgKwIv/metadata.json"
    );
    console.log("Modelo carregado com sucesso!");
    setupWebcam();
}

async function setupWebcam() {
    const video = document.getElementById("webcam");

    const stream = await navigator.mediaDevices.getUserMedia({ 
        video: true 
    });

    video.srcObject = stream;
    video.play();

    setInterval(() => classifyImage(), 5000);  // O intervalo de 2 segundos para classificação
}

async function classifyImage() {
    if (!model || isSending) return;  // Impede enviar comandos rapidamente
    isSending = true;

    const prediction = await model.predict(document.getElementById("webcam"));

    const highestPrediction = prediction.sort((a, b) => b.probability - a.probability)[0];

    console.log(`Material detectado: ${highestPrediction.className} com probabilidade: ${highestPrediction.probability.toFixed(2)}`);
    sendToArduino(highestPrediction.className);

    const consoleOutput = document.getElementById('console-output');

    consoleOutput.innerHTML = `
        <p>Material detectado: ${highestPrediction.className}</p>
        <p>Probabilidade: ${highestPrediction.probability.toFixed(2)}</p>
    `;

    // Aguardar um pouco antes de permitir enviar o próximo comando
    setTimeout(() => isSending = false, 1500); // Ajuste para garantir que o servo tenha tempo de mover
}

document.getElementById("connectButton").addEventListener("click", async () => {
    try {
        serialPort = await navigator.serial.requestPort();
        await serialPort.open({ baudRate: 9600 });
        console.log("Conectado ao Arduino!");
        writer = serialPort.writable.getWriter();  // Apenas abre a porta, sem enviar dados
        await writer.write(new TextEncoder().encode("a"));
    } catch (error) {
        console.error("Erro ao conectar ao Arduino: ", error);
    }
});

async function sendToArduino(material) {
    if (writer) {
        var com;
        if (material == "plastico") {
            com = "p"
        }
        else{
            com = "t";
        }
        await writer.write(new TextEncoder().encode(com));  // Escreve na porta serial
        console.log(`Comando enviado: ${com}`);
    }
    else{
        console.log("asdasdasdasd");
    }
}

loadModel();
