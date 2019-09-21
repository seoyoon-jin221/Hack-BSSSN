function distanceKnob() {
    // Create knob element, 300 x 300 px in size.
    var knob = pureknob.createKnob(300, 300);
    
    // Set properties.
    knob.setProperty('angleStart', -1 * Math.PI);
    knob.setProperty('angleEnd', 1 * Math.PI);
    knob.setProperty('colorFG', 'black');
    knob.setProperty('trackWidth', 0.4);
    knob.setProperty('valMin', 0);
    knob.setProperty('valMax', 60);
    
    // Set initial value.
    knob.setValue(0);
    

    var listener = function(knob, value) {
        console.log(value);
        sendValue = value;
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
    b.innerText = "Send Distance";
    elem.appendChild(b);
    var parent = document.getElementById('controlsView');
    parent.appendChild(elem);

}


function ready() {
    distanceKnob();
    
}

document.addEventListener('DOMContentLoaded', ready, false);