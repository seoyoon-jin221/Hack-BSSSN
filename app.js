// Sets console.log() to print to Evothings console
if (window.hyper && window.hyper.log) { console.log = hyper.log }

document.addEventListener(
    'deviceready',
    function() { 
        app.initialize();
    }
);

var servoControl = document.getElementById('servo-control');

var servoButtons = servoControl.getElementsByClassName('button');


var app = {}

app.SERVICE_UUID='0000ffe0-0000-1000-8000-00805f9b34fb';
app.CHARACTERISTIC_UUID='0000ffe1-0000-1000-8000-00805f9b34fb';
app.DEVICE_ADDRESS='94FA5DEC-0AC4-1C23-D78B-2682D43CAA83'

app.initialize = function()
{
    console.log('Initialized');
    app.connected = false;
    app.device = null;
}

app.connect = function()
{
    console.log('Attempting to connect to bluetooth module');

    evothings.easyble.startScan(scanSuccess,scanFailure, {serviceUUIDS : [app.SERVICE_UUID]}, { allowDuplicates: true});
}

var count = 0;
function scanSuccess(device)
{
    if(device.name != null)
    {
        console.log('Found' + ' ' + count + ' ' + device.name);
        
        console.log('Device Address: ' + device.address);
        
        if (device.address = app.DEVICE_ADDRESS) {
            device.connect(connectSuccess,connectFailure);
            evothings.easyble.stopScan();
        }
        
    }
}

function scanFailure(errorCode)
{
    console.log('Error ' + errorCode);
}

function connectSuccess(device)
{
    console.log('Successfully connected!!');
    app.connected = true;
    app.device = device; 
    app.device.readServices(serviceSuccess, serviceFailure, [ app.SERVICE_UUID]);
}

function connectFailure()
{
    app.connected = false;
    console.log('Failed to connect! :( ');
}

app.disconnect = function(errorMessage)
{
    if(errorMessage)
    {
        console.log(errorMessage);
    }
    app.connected = false;
    app.device = null;

    evothings.easyble.stopScan();
    evothings.easyble.closeConnectedDevices();
    app.showStart();
    
}

function serviceSuccess(device)
{
    console.log('The bluetooth module can now read and write');
    app.showControls();
    app.device.writeCharacteristic(
        app.SERVICE_UUID,
        function()
        {
            console.log('writeCharacteristic success');
        },
        function(errorCode)
        {
            console.log('writeCharacteristic error: ' + errorCode);
        });
    app.device.enableNotification(
        app.SERVICE_UUID,
        app.CHARACTERISTIC_UUID,
        app.receivedData,
        function(errorCode)
        {
            console.log('Failed to receive notification from device' + errorCode);
        },
        { writeConfigDescriptor: false }
    );

}

function serviceFailure(errorCode)
{
    console.log('Failed to read services' + errorCode);
    app.disconnect();
}

app.sendData = function(data)
{
    if (app.connected && app.device != null)
    {
        data = new Uint8Array(data);
        app.device.writeCharacteristic(
            app.CHARACTERISTIC_UUID,
            data,
            function ()
            {
                console.log('Succeed to send message!' + data);
            },
            function (errorCode)
            {
                console.log('Failed to send message!' + errorCode);
            }
        );
    }
    else
    {
        app.disconnect('Device was disconnected when trying to send message');
    }
}

app.receivedData = function(data)
{
    //0X16
    if(data == 0x16)
    {    //vibrate the phone, change the color of button, .... 
    }
}


app.showControls = function()
{
    $('#disconnect').prop('disabled', false);
    $('#startView').hide();
    $('#controlsView').show();
}

app.showStart = function()
{
    $('#disconnect').prop('disabled', true);
    $('#startView').show();
    $('#controlsView').hide();
}

app.displayServoAngle = function() {
    
}

app.increaseServoAngle = function() {
    app.sendData(new Uint8Array([1]));
}

app.decreaseServoAngle = function() {
    app.sendData(new Uint8Array([0]));
}

app.stopServoAngle = function() {
    app.sendData(new Uint8Array([2]))
}


function rotateStepper(angle) {
    if (angle > 0) {
        app.sendData([0, angle]);
    } 
    else if (angle < 0) {
        app.sendData([1, -angle]);
    }    
}

function setHeight(height) {
    app.sendData([2, height]);

}

function setDistance(distance) {
    app.sendData([3, distance]);
}

function setClaw(grasp) {
    app.sendData([4, grasp]);
}

function openClaw() {
    setClaw(0);
}

function closeClaw() {
    setClaw(90);
}

function stepCloseClaw() {
    app.sendData([5]);
}