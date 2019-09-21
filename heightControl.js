var heightValue;
function heightKnob() {
    // Create knob element, 300 x 300 px in size.
    var knob = pureknob.createKnob(300, 300);
    
    // Set properties.
    knob.setProperty('angleStart', -1 * Math.PI);
    knob.setProperty('angleEnd', 1 * Math.PI);
    knob.setProperty('colorFG', 'indigo');
    knob.setProperty('trackWidth', 0.4);
    knob.setProperty('valMin', 0);
    knob.setProperty('valMax', 90);
    
    // Set initial value.
    knob.setValue(0);
    

    var listener = function(knob, value) {
        console.log(value);
        heightValue = value;
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
    b.innerText = "Send Height";
    elem.appendChild(b);
    var parent = document.getElementById('controlsView');
    parent.appendChild(elem);
    b.addEventListener('touchstart', function() {
        console.log("height clicked");
        setHeight(heightValue);
    });

    var stepIncreaseHeightButton = document.createElement("button");
    stepIncreaseHeightButton.className = "btn btn-outline-secondary";
    stepIncreaseHeightButton.innerText = "Step Increase Height";
    elem.appendChild(stepIncreaseHeightButton);
    stepIncreaseHeightButton.addEventListener('touchstart', function() {
        stepIncreaseHeight();
    })
    
    //step closeclawbubtton
    var stepDecreaseHeightButton = document.createElement("button");
    stepDecreaseHeightButton.className = "btn btn-outline-secondary";
    stepDecreaseHeightButton.innerText = "Step Decrease Height";
    elem.appendChild(stepDecreaseHeightButton);
    stepDecreaseHeightButton.addEventListener('touchstart', function() {
        stepDecreaseHeight();
    })
}


function ready() {
    heightKnob();
    
}

document.addEventListener('DOMContentLoaded', ready, false);