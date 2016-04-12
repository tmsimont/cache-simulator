function EventTimeline(target) {
  var ET = this;

  // settings -------------------------------------------
  // time index in arbitrary units
  ET.currentTime = 0;

  // arbitrary time index unit at which timeline ends
  ET.timeEnd = 5000;

  // translation of arbitrary units to miliseconds
  ET.timeUnitMS = 200;

  // number of arbitrary time units per axis
  ET.minorAxisUnits = 5;
  ET.majorAxisUnits = 10;
  ET.totalMinor = ET.timeEnd / ET.minorAxisUnits;
  ET.totalMajor = ET.timeEnd / ET.majorAxisUnits;


  // initial state --------------------------------------
  ET.playing = false;
  ET.needleX = 0;
  ET.viewportStart = ET.currentTime;
  ET.viewportNeedleUnit = 0;
  ET.viewportUnits = 100;
  ET.viewportEnd = ET.viewportUnits;
  ET.viewportNeedleOffset = 0;
  ET.drawnUnits = {};
  ET.drawnMin = 0;
  ET.drawnMax = 0;
  ET.events = {};

  
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

  // todo: multiple rows of events?
  ET.eventContainer = $("<div>");
  ET.eventContainer.addClass("event-container");
  ET.container.prepend(ET.eventContainer);

  ET.container.prepend(ET.axisContainer);
  ET.addControls(target);

}

EventTimeline.prototype.init = function() {
  var ET = this;
  // call setter to initialize viewport
  ET.setViewportSize(ET.viewportUnits);
}

EventTimeline.prototype.setViewportSize = function(units) {
  var ET = this;

  if (units < 0) return;
  if (units > 500) return;

  $(".velocity-animating").velocity("stop", true);
  ET.viewportUnits = units;
  ET.viewportStart = Math.floor(ET.currentTime - units/2);

  if (ET.viewportStart < 0) ET.viewportStart = 0;

  // set values senstive to rendered width/height in pixels
  ET.calculateViewportSize();
  ET.positionNeedle(true);
  ET.drawCurrentViewport(true);
}

/**
 * Calculate pixel sizes of axes and viewport window
 * based on timeline container and viewport relative size
 */
EventTimeline.prototype.calculateViewportSize = function() {
  var ET = this;

  // relative sizing viewport relative size
  ET.viewportUnitPX = $(ET.container).width() / ET.viewportUnits;
}

EventTimeline.prototype.drawCurrentViewport = function(immediate) {
  var ET = this;

  var buffer = ET.minorAxisUnits;
  
  // make buffer large enough for longest event
  ET.eventContainer.find(".event-element").each(function() {
    var unitWidth = parseInt($(this).data("unitWidth"));
    if (unitWidth > buffer) buffer = unitWidth;
  });
  
  // draw units for time window in viewport
  
  for (var i = 0 - buffer; i < ET.viewportUnits + buffer; i++) {
    var timeHere = ET.viewportStart + i;

    // don't redraw drawn units
    // todo: support dynamic adding of events?
    if (!ET.drawnUnits[timeHere]) {
      ET.drawUnits(timeHere);
    }

    // some drawn units might need adjustment
    else {
      for (var j = 0; j < ET.drawnUnits[timeHere].length; j++) { 
        var originalVPU = $(ET.drawnUnits[timeHere][j]).data("originalVPU");
        var originalVPX = $(ET.drawnUnits[timeHere][j]).data("originalVPX");

        // resize if needed
        if (ET.viewportUnitPX != originalVPX) {
          var unitWidth = $(ET.drawnUnits[timeHere][j]).data("unitWidth");

          $(ET.drawnUnits[timeHere][j]).velocity("stop");
          $(ET.drawnUnits[timeHere][j]).width(ET.viewportUnitPX * unitWidth);
          $(ET.drawnUnits[timeHere][j]).css(
            "left",
            originalVPU * ET.viewportUnitPX
          );
        }

        // shift drawn units if we have movement of viewport
        var offset = originalVPU - i;
        if (offset != 0) {
          if (immediate) {
            $(ET.drawnUnits[timeHere][j]).css({
              left : "-=" + (offset * ET.viewportUnitPX)
            });
          }
          else {
            $(ET.drawnUnits[timeHere][j]).velocity({
              left : "-=" + (offset * ET.viewportUnitPX)
            },{
              easing: "linear",
              queue : false,
              duration: ET.timeUnitMS,
            });
          }
        }

        $(ET.drawnUnits[timeHere][j]).data("originalVPU", i);
        $(ET.drawnUnits[timeHere][j]).data("originalVPX", ET.viewportUnitPX);
      }
    }
  }

  // keep pointers to time range we have drawn
  ET.drawnMin = ET.viewportStart;
  ET.drawnMax = ET.viewportStart + ET.viewportUnits - 1;

  // clear out drawn elements outside of time range + buffer
  for (var i = 0; i < ET.drawnMin - buffer; i++) {
    if (ET.drawnUnits[i]) {
      for (var j = 0; j < ET.drawnUnits[i].length; j++) {
        var e = ET.drawnUnits[i][j].data("event");
        if (e) e.drawn = false;
        ET.drawnUnits[i][j].remove();
      }
      ET.drawnUnits[i] = false;
    }
  }
  for (var i = 1 + ET.drawnMax + buffer; i <= ET.timeEnd; i++) {
    if (ET.drawnUnits[i]) {
      for (var j = 0; j < ET.drawnUnits[i].length; j++) {
        var e = ET.drawnUnits[i][j].data("event");
        if (e) e.drawn = false;
        ET.drawnUnits[i][j].remove();
      }
      ET.drawnUnits[i] = false;
    }
  }

}

EventTimeline.prototype.drawUnits = function(time) {
  var ET = this;
  
  if (!ET.drawnUnits[time]) {
    ET.drawnUnits[time] = [];
  }

  // get events at this time and draw
  // todo
  if (ET.events[time]) {
    for (var i = 0; i < ET.events[time].length; i++) {
      ET.addTimelineElement(time, ET.events[time][i]);
    }
  }

  // get axis at this time and draw
  if (time % ET.minorAxisUnits == 0)
    ET.addAxis(time);
}

EventTimeline.prototype.moveViewport = function(offsetUnits) {
  var ET = this;
  ET.viewportStart += offsetUnits;
  ET.drawCurrentViewport();
}

/**
 * Add a dom element at a set time that is a set number of time units wide.
 */
EventTimeline.prototype.addElement = function(time, unitWidth, element) {
  var ET = this;

  // viewport-sensitive positioning and sizing
  var viewportUnit = time - ET.viewportStart;
  element.css("left", viewportUnit * ET.viewportUnitPX);
  element.data("originalVPU", viewportUnit);
  element.data("originalVPX", ET.viewportUnitPX);
  element.data("unitWidth", unitWidth);
  element.width(ET.viewportUnitPX * unitWidth);
  
  // keep track of the element
  ET.drawnUnits[time].push(element);
}

EventTimeline.prototype.addTimelineElement = function(time, e) {
  var ET = this;

  if (e.drawn) {
  }
  else {
    var element = e.timelineRendering();
    var width = e.getUnitWidth();
    ET.addElement(time, width, element);
    ET.eventContainer.append(element);
    element.addClass("event-element");
    element.data("event", e);
    e.element = element;
    e.drawn = true;
  }
}

EventTimeline.prototype.addAxis = function(axisUnit) {
  var ET = this;

  // axis is a div
  var line = $("<div>");


  line.addClass("axis");
  if (axisUnit % ET.majorAxisUnits == 0) {
    line.addClass("axis-major");
  }
  else {
    line.addClass("axis-minor");
  }

  ET.addElement(axisUnit, ET.minorAxisUnits, line);
  ET.axisContainer.append(line);
}

EventTimeline.prototype.play = function() {
  var ET = this;
  if (!ET.playing) {
    ET.playing = true;
    ET.eventLoop();
  }
}

EventTimeline.prototype.pause = function() {
  var ET = this;
  ET.playing = false;
}


EventTimeline.prototype.eventLoop = function() {
  var ET = this;

  // nothing more to do at the end of time...
  if (ET.currentTime >= ET.timeEnd)
    ET.playing = false;

  if (ET.playing) {
    ET.activateEvents();
    ET.currentTime++;
    ET.positionNeedle();
    setTimeout(function() {
      ET.eventLoop();
    }, ET.timeUnitMS);
  }
}

EventTimeline.prototype.activateEvents = function() {
  var ET = this;
  if (ET.events[ET.currentTime]) {
    for (var i = 0; i < ET.events[ET.currentTime].length; i++) {
      var e = ET.events[ET.currentTime][i];
      e.activate(ET.currentTime, ET);
    }
  // todo
  }
}


EventTimeline.prototype.positionNeedle = function(immediate) {
  var ET = this;
  ET.viewportNeedleUnit = ET.currentTime - ET.viewportStart;

  if (immediate) {
    $(ET.needle).css({
      left : ET.viewportNeedleUnit * ET.viewportUnitPX
    });
    return;
  }

  // have to move viewport
  if (ET.viewportNeedleUnit >= ET.viewportUnits / 2) {
    ET.moveViewport(+1)
    return;
  }
  // advance within viewport
  else {
    $(ET.needle).velocity({
      left : ET.viewportNeedleUnit * ET.viewportUnitPX
    },{
      easing: "linear",
      queue: false,
      duration: ET.timeUnitMS,
    });
  }
}

EventTimeline.prototype.gotoTime = function(unit) {
  var ET = this;
  ET.currentTime = unit;
  ET.positionNeedle(true);
  if (unit > ET.viewportStart + (ET.viewportUnits / 2)) {
    ET.setViewportSize(ET.viewportUnits);
  }
  if (unit < ET.viewportStart) {
    ET.viewportStart = unit;
    ET.setViewportSize(ET.viewportUnits);
  }
}


EventTimeline.prototype.addControls = function(target) {
  var ET = this;


  $(target).on("mousewheel", function(event) {
    ET.setViewportSize(ET.viewportUnits - (event.deltaY * 10));
  });

  $(ET.container).on("click", function(event) {
    //ET.viewportUnitPX = $(ET.container).width() / ET.viewportUnits;
    var clickedViewportUnit = event.clientX / ET.viewportUnitPX;
    var clickedTime = ET.viewportStart + clickedViewportUnit;
    var unit = Math.floor(clickedTime);
    ET.gotoTime(clickedTime);
  });

  var speedUp = $("<button>");
  speedUp.text("+");
  $(target).append(speedUp);
  speedUp.click(function() {
    ET.timeUnitMS -= 10;
  });

  var speedDown = $("<button>");
  speedDown.text("-");
  $(target).append(speedDown);
  speedDown.click(function() {
    ET.timeUnitMS += 10;
  });


  var pause = $("<button>");
  pause.text("||");
  $(target).append(pause);
  pause.click(function() {
    ET.pause();
  });

  var play = $("<button>");
  play.text(">");
  $(target).append(play);
  play.click(function() {
    ET.play();
  });

  var rewind = $("<button>");
  rewind.text("<<");
  $(target).append(rewind);
  rewind.click(function() {
    ET.gotoTime(0);
  });



  var zoomIn = $("<button>");
  zoomIn.text("in");
  $(target).append(zoomIn);
  zoomIn.click(function() {
    ET.setViewportSize(ET.viewportUnits - 10);
  });

  var zoomOut = $("<button>");
  zoomOut.text("out");
  $(target).append(zoomOut);
  zoomOut.click(function() {
    ET.setViewportSize(ET.viewportUnits + 10);
  });
}

function Event(activation, deactivation) {
  var E = this;
  this.start = 0;
  this.end = 0;
  this.title = "event"

  this.drawn = false;
  this.element = {};

  this.getUnitWidth = function() {
    return this.end - this.start;
  }
  this.timelineRendering = function() {
    var render = $("<div>");
    render.text(E.title);
    return render;
  }
  
  
  this.activate = function(currentTime, ET) {
    var relTime = currentTime - E.start;
    E.element.addClass("active-event");
    activation(relTime, E);
    if (currentTime == E.end) {
      setTimeout(function() {
        E.element.removeClass("active-event");
        E.deactivate();
      }, ET.timeUnitMS);
    } 
  }

  this.deactivate = function() {
    deactivation(E);
  }

}

EventTimeline.prototype.addEvent = function(eventType) {
  var ET = this;
  var e = new Event(
    function(time, E) {
      eventType.animate(time, E);
    },
    function(E) {
      eventType.finish(E);
    }
  );
  for (var i in eventType.params) {
    e[i] = eventType.params[i];
  }

  // todo: support dynamic adding of events?
  for (var t = e.start; t <= e.end; t++) {
    if (!ET.events[t]) {
      ET.events[t] = [];
    }
    ET.events[t].push(e);
  }

}
