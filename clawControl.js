var clawValue = 0;
function clawKnob() {
    // Create knob element, 300 x 300 px in size.
    var knob = pureknob.createKnob(300, 300);
    
    // Set properties.
    knob.setProperty('angleStart', -1 * Math.PI);
    knob.setProperty('angleEnd', 1 * Math.PI);
    knob.setProperty('colorFG', 'red');
    knob.setProperty('trackWidth', 0.4);
    knob.setProperty('valMin', -180);
    knob.setProperty('valMax', 180);
    
    // Set initial value.
    knob.setValue(0);
    

    var listener = function(knob, value) {
        console.log(value);
        clawValue = value;
        //set the listener to send the value
    };
    
    knob.addListener(listener);
    
    // Create element node.
    var node = knob.node();
    
    node.style.setProperty('float','left');

    // Add it to the DOM.
    var elem = document.createElement("div");
    elem.appendChild(node);
    
    var b = document.createElement("button");
    b.className = "btn btn-outline-secondary";
    b.innerText = "Send Claw";
    elem.appendChild(b);

    var parent = document.getElementById('controlsView');
    parent.appendChild(elem);
    b.addEventListener('touchstart', function() {
        setClaw(clawValue);
    });

    var closeClawButton = document.createElement("button");
    closeClawButton.className = "btn btn-outline-secondary";
    closeClawButton.innerText = "Close Claw Completely";
    elem.appendChild(closeClawButton);
    
    var openClawButton = document.createElement("button");
    openClawButton.className = "btn btn-outline-secondary";
    openClawButton.innerText = "Open Claw";
    elem.appendChild(closeClawButton);
    
    //step closeclawbubtton
    var stepCloseClawButton = document.createElement("button");
    stepCloseClawButton.className = "btn btn-outline-secondary";
    stepCloseClawButton.innerText = "Step Close Claw";
    elem.appendChild(stepCloseClawButton);

    var parent = document.getElementById('controlsView');
    parent.appendChild(elem);
}


function ready() {
    clawKnob();
    
}

document.addEventListener('DOMContentLoaded', ready, false);