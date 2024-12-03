let model;
let serialPort = null; // Inicialmente, sem conexão
let writer = null;
const classNames = ["tampinha_plastico", "bolinha_papel", "espaco_vazio"]; // Incluindo "espaco_vazio"

// Limiar de probabilidade para detectar "espaço vazio"
const emptyThreshold = 0.7;

async function loadModel() {
    model = await tmImage.load(
        "https://teachablemachine.withgoogle.com/models/SBrG01kNB/model.json",
        "https://teachablemachine.withgoogle.com/models/SBrG01kNB/metadata.json"
    );
    console.log("Modelo carregado com sucesso!");
    setupWebcam();
}

async function setupWebcam() {
    const video = document.getElementById("webcam");

    const stream = await navigator.mediaDevices.getUserMedia({
        video: true,
    });

    video.srcObject = stream;
    video.play();

    // Faz a classificação continuamente
    setInterval(() => classifyImage(), 5000); // Intervalo de 5 segundos
}

async function classifyImage() {
    if (!model) return; // Aguarda o modelo ser carregado

    const predictions = await model.predict(document.getElementById("webcam"));
    const highestPrediction = predictions.sort((a, b) => b.probability - a.probability)[0];

    let material;
    const probability = highestPrediction.probability.toFixed(2);

    // Verifica se o material identificado tem uma probabilidade acima do limiar
    if (highestPrediction.probability >= emptyThreshold) {
        material = highestPrediction.className;
    } else {
        material = "espaco_vazio"; // Classifica como "espaço vazio"
    }

    console.log(`Material detectado: ${material} com probabilidade: ${probability}`);

    // Atualiza o HTML com as informações detectadas
    const consoleOutput = document.getElementById("console-output");
    consoleOutput.innerHTML = `
        <p>Material detectado: ${material}</p>
        <p>Probabilidade: ${probability}</p>
    `;

    // Envia o resultado para o Arduino, caso esteja conectado
    if (serialPort && writer) {
        sendToArduino(material);
    }
}

document.getElementById("connectButton").addEventListener("click", async () => {
    try {
        // Solicita permissão para conectar à porta serial
        serialPort = await navigator.serial.requestPort();
        await serialPort.open({ baudRate: 9600 });
        console.log("Conectado ao Arduino!");

        // Cria o writer para enviar comandos ao Arduino
        writer = serialPort.writable.getWriter();
        await writer.write(new TextEncoder().encode("a")); // Sinal de inicialização
    } catch (error) {
        console.error("Erro ao conectar ao Arduino: ", error);
    }
});

async function sendToArduino(material) {
    if (!writer) {
        console.error("Erro: Nenhuma conexão com o Arduino.");
        return;
    }

    let command;
    if (material === "tampinha_plastico") {
        command = "p"; // Comando para tampinha de plástico
    } else if (material === "bolinha_papel") {
        command = "b"; // Comando para bolinha de papel
    } else if (material === "espaco_vazio") {
        command = "v"; // Comando para espaço vazio
    }

    await writer.write(new TextEncoder().encode(command)); // Envia o comando
    console.log(`Comando enviado para o Arduino: ${command}`);
}

// Carrega o modelo ao iniciar
loadModel();


