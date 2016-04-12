function EventTimeline(target) {
  var ET = this;

  // settings -------------------------------------------
  // time index in arbitrary units
  ET.currentTime = 0;

  // arbitrary time index unit at which timeline ends
  ET.timeEnd = 5000;

  // translation of arbitrary units to miliseconds
  ET.timeUnitMS = 600;

  // number of arbitrary time units per axis
  ET.minorAxisUnits = 5;
  ET.majorAxisUnits = 10;
  ET.totalMinor = ET.timeEnd / ET.minorAxisUnits;
  ET.totalMajor = ET.timeEnd / ET.majorAxisUnits;


  // initial state --------------------------------------
  ET.playing = false;
  ET.needleX = 0;
  ET.viewportStart = ET.currentTime;
  ET.viewportNeedleX = 0;
  ET.viewportUnits = 20;
  ET.viewportEnd = ET.viewportUnits;
  ET.viewportNeedleOffset = 0;

  
  // build timeline dom elements ------------------------
  $(target).addClass("timeline-target");
  ET.container = $("<div>");
  ET.container.addClass("timeline-container");
  target.append(ET.container);
  ET.needle = $("<div>");
  ET.needle.addClass("needle");
  ET.container.append(ET.needle);
  ET.axisContainer = $("<div>");
  ET.axisContainer.addClass("axis-container");
  ET.container.prepend(ET.axisContainer);

  // set values senstive to rendered width/height in pixels
  ET.calculateViewportValues();
  ET.addElementsToViewport();
  ET.calculateNeedleValues();

  // start playing
  ET.play();
  
}

EventTimeline.prototype.calculateViewportValues = function() {
  var ET = this;
  // relative sizing viewport relative size
  ET.viewportPercentage = ET.viewportUnits / ET.timeEnd;
  ET.viewportPX = $(ET.container).width();

  // axes based on total axes and axes that can fit in viewport
  ET.viewportMinorAxes = ET.viewportPercentage * ET.totalMinor;
  ET.minorAxisPX = ET.viewportPX / ET.viewportMinorAxes;
}

EventTimeline.prototype.addElementsToViewport = function() {
  var ET = this;
  // axes offset based on viewportStart
  var start = 0;
  var offsetUnits = ET.viewportStart % ET.minorAxisUnits;
  var offsetPX = -1 * (ET.minorAxisPX * offsetUnits / ET.minorAxisUnits);
  if (offsetUnits > 0) start = 1;
  for (var i = start; i < ET.viewportMinorAxes + start; i++) {
    ET.addAxis(offsetUnits, offsetPX, i);
  }
}
EventTimeline.prototype.addAxis = function(offsetUnits, offsetPX, i) {
  var ET = this;
  var line = $("<div>");
  line.css("left", offsetPX + (i * ET.minorAxisPX));
  line.width(ET.minorAxisPX);
  line.addClass("axis");
  if (i % ( ET.totalMinor / ET.totalMajor ) == 0) {
    line.addClass("axis-major");
  }
  else {
    line.addClass("axis-minor");
  }
  ET.axisContainer.append(line);
}

EventTimeline.prototype.calculateNeedleValues = function() {
  var ET = this;
  // needle moves this much at each time unit
  ET.needleIncrement = $(ET.container).width() / ET.viewportUnits;
  //ET.needle.css("transition", "transform " + (ET.timeUnitMS) +"ms linear");
}

EventTimeline.prototype.setAxesValues = function() {
}

EventTimeline.prototype.addAxes = function() {
  
}

EventTimeline.prototype.play = function() {
  var ET = this;
  ET.playing = true;
  ET.eventLoop();
}

EventTimeline.prototype.eventLoop = function() {
  var ET = this;

  // nothing more to do at the end of time...
  if (ET.currentTime >= ET.timeEnd)
    ET.playing = false;

  if (ET.playing) {
    ET.activateEvents();
    ET.advanceNeedle();
    ET.currentTime++;
    setTimeout(function() {
      ET.eventLoop();
    }, ET.timeUnitMS);
  }
}

EventTimeline.prototype.activateEvents = function() {
  var ET = this;
}


EventTimeline.prototype.advanceNeedle = function() {
  var ET = this;

  // have to move viewport
  if (ET.currentTime >= (ET.viewportStart + ET.viewportUnits) / 2) {


    /*
    // TRYING TO ADD IN NEW AXES

    if (ET.viewportStart % ET.majorAxisUnits == 0) {
      ET.viewportNeedleOffset = 0;
    }


    if (ET.viewportStart % ET.minorAxisUnits == 0) {
      var offsetUnits = ET.viewportStart % ET.minorAxisUnits;
      var offsetPX = -1 * (ET.minorAxisPX * offsetUnits / ET.minorAxisUnits);
      var idx = ET.axisContainer.find(".axis").length;
      ET.addAxis(offsetUnits, offsetPX, idx);
    }

    ET.viewportStart++; 
    ET.viewportNeedleOffset -= ET.needleIncrement;
    ET.axisContainer.find(".axis").each(function() {
      $(this).css(
          "transform",
          "translate3d(" + ET.viewportNeedleOffset + "px, 0px, 0px)"
      );
    });
    */


    // TRYING TO RECREATE AXES
    /*
    ET.viewportStart++; 
    if (ET.viewportStart % ET.minorAxisUnits == 0) {
      ET.viewportNeedleOffset = 0;
    }
    else {
      ET.viewportNeedleOffset -= ET.needleIncrement;
      ET.axisContainer.find(".axis").each(function() {
        $(this).css(
            "transition",
            "transform " + (ET.timeUnitMS) + "ms linear"
        );
        $(this).css(
            "transform",
            "translate3d(" + ET.viewportNeedleOffset + "px, 0px, 0px)"
        );
      });
    }
    // can try to time out with end of motion, but results in race
    ET.axisContainer.find("div").remove();
    ET.calculateViewportValues();
    ET.addElementsToViewport();
    */
    return;
  }
  // advance within viewport
  else {
    ET.viewportNeedleX += ET.needleIncrement;
    $(ET.needle).css(
        "transform",
        "translate3d(" + ET.viewportNeedleX + "px, 0px, 0px)"
    );
  }
}
