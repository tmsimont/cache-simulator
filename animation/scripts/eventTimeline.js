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
  ET.drawnAxes = {};
  ET.elementsInView = [];
  ET.elementsAtTimeUnit = {};
  ET.drawnMin = 0;
  ET.drawnMax = 0;
  ET.events = {};
  ET.immediate = false;
  ET.lastActivation = -1;

  
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

EventTimeline.prototype.init = function(onready) {
  var ET = this;
  // call setter to initialize viewport
  ET.setViewportSize(ET.viewportUnits);
  if (typeof onready == "function") {
    onready();
  }  
}

EventTimeline.prototype.setViewportSize = function(units) {
  var ET = this;

  // impose limits on timeline size
  if (units < 2) return;
  if (units > 500) return;

  ET.immediateAction(function() {
    // reset values
    ET.viewportUnits = units;
    ET.viewportStart = Math.floor(ET.currentTime - units/2);

    // min is 0
    if (ET.viewportStart < 0) ET.viewportStart = 0;

    // max is timeEnd - viewportStart
    if (ET.viewportStart + ET.viewportUnits > ET.timeEnd) {
    ET.viewportStart = ET.timeEnd - Et.viewportUnits;
    }

    // calculate time unit to pixel ratio
    ET.viewportUnitPX = $(ET.container).width() / ET.viewportUnits;

    // immediately reposition needle
    ET.positionNeedle();
    ET.drawCurrentViewport();
  });
}

EventTimeline.prototype.drawCurrentViewport = function() {
  var ET = this;

  // buffer for time range outside of window to load in events
  var buffer = ET.minorAxisUnits;
  
  // draw new units for time window in (viewport + buffer)
  for (var i = 0 - buffer; i < ET.viewportUnits + buffer; i++) {
    ET.drawUnits(ET.viewportStart + i);
  }

  // update existing units between drawnMin and drawnMax
  for (var i = ET.drawnMin; i <= ET.drawnMax; i++) {
    ET.updateUnits(ET.viewportStart + i);
  }

  // clear out drawn units before buffer
  for (var i = ET.drawnMin; i < ET.viewportStart - buffer; i++) {
    if (ET.drawnUnits[i]) {
      for (var j = 0; j < ET.drawnUnits[i].length; j++) {
        if (ET.drawnUnits[i][j].end < ET.viewportStart - buffer) {
          ET.drawnUnits[i][j].destroy();
        }
        else {
          if (ET.drawnMin > ET.drawnUnits[i][j].start) {
            ET.drawnMin = ET.drawnUnits[i][j].start;
          }
        }
      }
    }
  }

  // clear out drawn units after buffer
  var start = ET.viewportStart + ET.viewportUnits + buffer;
  for (var i = start; i <= ET.drawnMax; i++) {
    if (ET.drawnUnits[i]) {
      for (var j = 0; j < ET.drawnUnits[i].length; j++) {
        if (ET.drawnUnits[i][j].start > start) {
          ET.drawnUnits[i][j].destroy();
        }
        else {
          if (ET.drawnMax < ET.drawnUnits[i][j].end) {
            ET.drawnMax = ET.drawnUnits[i][j].end;
          }
        }
      }
    }
  }
}

EventTimeline.prototype.drawUnits = function(time) {
  var ET = this;
  
  // get events at this time and draw
  if (ET.events[time]) {
    for (var i = 0; i < ET.events[time].length; i++) {
      ET.drawEvent(time, ET.events[time][i]);
    }
  }

  // might need to add an axis element
  if (!ET.drawnAxes[time]) {
    if (time % ET.minorAxisUnits == 0)
      ET.addAxis(time);
  }

  // keep a range of drawn elements
  if (time < ET.drawnMin) ET.drawnMin = time;
  if (time > ET.drawnMax) ET.drawnMax = time;
}

EventTimeline.prototype.updateUnits = function(timeAtI) {
  var ET = this;

  if (ET.drawnUnits[timeAtI]) {
    for (var j = 0; j < ET.drawnUnits[timeAtI].length; j++) { 
      var te = ET.drawnUnits[timeAtI][j];

      // immediately update size on viewport resize
      if (ET.viewportUnitPX != te.drawnViewportUnitPX) {
        te.updateToViewport();
      }

      // animate viewport motion if viewport has moved
      else if (te.drawnViewportUnit != (te.start - ET.viewportStart)) {
        te.animateMotion();
      }
    }
  }
}

EventTimeline.prototype.moveViewport = function(offsetUnits) {
  var ET = this;
  ET.viewportStart += offsetUnits;
  ET.drawCurrentViewport();
}

EventTimeline.prototype.drawEvent = function(time, e) {
  var ET = this;
  if (e.drawn) {
    e.includeInstanceAtTime(time);
  }
  else {
    ET.eventContainer.append(e.newViewportInstance());
  }
}

EventTimeline.prototype.addAxis = function(time) {
  var ET = this;

  // axis is a div
  var line = $("<div>");
  line.addClass("axis");

  // determine major vs. minor
  if (time % ET.majorAxisUnits == 0) {
    line.addClass("axis-major");
  }
  else {
    line.addClass("axis-minor");
  }

  // generate viewport instance
  var viewportInstance = ET.drawToViewport(
    time, ET.minorAxisUnits, line
  );

  // override destructor
  viewportInstance.destroy = function() {
    line.remove();
    ET.drawnAxes[time] = false;
  }

  // axis is only 1 time unit
  viewportInstance.end = viewportInstance.start;

  // track globally 
  ET.drawnAxes[time] = viewportInstance;
  
  // add to DOM
  ET.axisContainer.append(line);
}

EventTimeline.prototype.drawToViewport = function(time, unitWidth, render) {
  var ET = this;

  function ViewportInstance() {
    var self = this;
    self.drawnViewportUnit = time - ET.viewportStart;
    self.drawnViewportUnitPX = ET.viewportUnitPX;
    self.render = render;
    self.unitWidth = unitWidth;
    self.start = time;
    self.end = time + unitWidth;

    // viewport-sensitive positioning and sizing
    self.fixElementView = function() {
      render.css(
        "left", self.drawnViewportUnit * self.drawnViewportUnitPX
      );
      render.width(self.drawnViewportUnitPX * self.unitWidth);
    }

    self.updateToViewport = function() {
      $(self.render).velocity("stop");
      self.drawnViewportUnit = self.start - ET.viewportStart;
      self.drawnViewportUnitPX = ET.viewportUnitPX;
      self.fixElementView();
    }

    self.animateMotion = function() {
      var newVPUnit = self.start - ET.viewportStart;
      var offset = self.drawnViewportUnit - newVPUnit;
      self.drawnViewportUnit = self.start - ET.viewportStart;
      if (!ET.immediate) {
        $(self.render).velocity({
          left : "-=" + (offset * ET.viewportUnitPX)
        },{
          easing: "linear",
          queue : false,
          duration: ET.timeUnitMS,
        });
      }
      else {
        self.fixElementView();
      }
    }

    self.destroy = function() {
      self.render.remove();
    }
  }

  // create closure and append to global table
  var viewportInstance = new ViewportInstance();
  viewportInstance.updateToViewport();
  if (!ET.drawnUnits[time]) {
    ET.drawnUnits[time] = [];
  }
  ET.drawnUnits[time].push(viewportInstance);
  return viewportInstance;
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
  if(ET.timeoutPending) {
    clearTimeout(ET.timeoutPending);
    ET.timeoutPending = false;
  }

  // stop any active velocity.js animations
  $(".velocity-animating").velocity("stop", true);
}


EventTimeline.prototype.eventLoop = function() {
  var ET = this;

  // nothing more to do at the end of time...
  if (ET.currentTime > ET.timeEnd) {
    ET.playing = false;
    return;
  }

  ET.activateEvents();
  ET.currentTime++;
  ET.positionNeedle();
  ET.timeoutPending = setTimeout(function() {
    ET.timeoutPending = false;
    if (ET.playing) {
      ET.eventLoop();
    }
  }, ET.timeUnitMS);
}

EventTimeline.prototype.immediateAction = function(action) {
  var ET = this;
  var resume = ET.playing;
  ET.pause();
  ET.immediate = true;
  action();
  ET.immediate = false;
  if (resume) ET.play();
}

EventTimeline.prototype.activateEvents = function() {
  var ET = this;
  if (ET.events[ET.lastActivation]) {
    for (var i = 0; i < ET.events[ET.lastActivation].length; i++) {
      var e = ET.events[ET.lastActivation][i];
      e.deactivate();
    }
  }
  if (ET.events[ET.currentTime]) {
    for (var i = 0; i < ET.events[ET.currentTime].length; i++) {
      var e = ET.events[ET.currentTime][i];
      e.activate();
    }
  }
  ET.lastActivation = ET.currentTime;
}

EventTimeline.prototype.positionNeedle = function() {
  var ET = this;
  ET.viewportNeedleUnit = ET.currentTime - ET.viewportStart;

  if (ET.immediate) {
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
  ET.immediateAction(function() {
    ET.currentTime = unit;
    ET.positionNeedle();
    if (unit > ET.viewportStart + (ET.viewportUnits / 2)) {
      ET.setViewportSize(ET.viewportUnits);
    }
    if (unit < ET.viewportStart) {
      ET.viewportStart = unit;
      ET.setViewportSize(ET.viewportUnits);
    }
  });
}

EventTimeline.prototype.addControls = function(target) {
  var ET = this;

  $(target).on("mousewheel", function(event) {
    ET.setViewportSize(ET.viewportUnits - (event.deltaY * 10));
  });

  $(ET.container).on("click", function(event) {
    var clickedViewportUnit = event.clientX / ET.viewportUnitPX;
    var clickedTime = ET.viewportStart + clickedViewportUnit;
    var unit = Math.floor(clickedTime);
    ET.gotoTime(unit);
  });

  
  var buttons = $("<div>");
  buttons.addClass("timeline-buttons");
  target.append(buttons)


  var speedUp = $("<button>");
  speedUp.text("+");
  $(buttons).append(speedUp);
  speedUp.click(function() {
    ET.timeUnitMS -= 10;
  });

  var speedDown = $("<button>");
  speedDown.text("-");
  $(buttons).append(speedDown);
  speedDown.click(function() {
    ET.timeUnitMS += 10;
  });


  var pause = $("<button>");
  pause.text("||");
  $(buttons).append(pause);
  pause.click(function() {
    ET.pause();
  });

  var play = $("<button>");
  play.text(">");
  $(buttons).append(play);
  play.click(function() {
    ET.play();
  });

  var rewind = $("<button>");
  rewind.text("<<");
  $(buttons).append(rewind);
  rewind.click(function() {
    ET.gotoTime(0);
  });

  var zoomIn = $("<button>");
  zoomIn.text("in");
  $(buttons).append(zoomIn);
  zoomIn.click(function() {
    ET.setViewportSize(ET.viewportUnits - 10);
  });

  var zoomOut = $("<button>");
  zoomOut.text("out");
  $(buttons).append(zoomOut);
  zoomOut.click(function() {
    ET.setViewportSize(ET.viewportUnits + 10);
  });
}


/**
 * @param: handler
 * handler is any object that has the following 
 * properties:
 *   start            : start time unit of event
 *   end              : end time unit of event
 *   title            : visible title on timeline
 *   activate(time)   : activation function at time
 *   deactivate(time) : deactivation function at time
 *   finish           : no longer in active time range
 *
 */
EventTimeline.prototype.addEvent = function(handler) {
  var ET = this;

  function Event() {
    var E = this;

    // set object properties from passed handler
    this.start = handler.start;
    this.end = handler.end;
    this.title = handler.title;

    this.drawn = false;
    this.render = {};
    this.drawnAt = [];

    this.getUnitWidth = function() {
      return this.end - this.start + 1;
    }

    this.newViewportInstance = function() {

      // set up dom element
      E.render = $("<div>");
      E.render.addClass("event-element");
      E.render.text(E.title);

      // create viewport instance
      var width = E.getUnitWidth();
      var viewportInstance = ET.drawToViewport(E.start, width, E.render);
      E.viewportInstance = viewportInstance;

      // override destructor
      viewportInstance.destroy = function() {
        E.render.remove();
        E.drawn = false;
        E.drawnAt = [];
      }
      E.drawn = true;

      // click event
      $(E.render).on("click", function() {
        ET.gotoTime(E.start);
        // prevent bubble up to container click
        return false;
      });

      return E.render;
    }

    this.includeInstanceAtTime = function(time) {
      // if already included, abort
      for (var i = 0; i < E.drawnAt.length; i++) { 
        if (time == E.drawnAt[i]) return;
      }

      // append existing viewportInstance to drawnUnits
      if (!ET.drawnUnits[time]) {
        ET.drawnUnits[time] = [];
      }
      ET.drawnUnits[time].push(e.viewportInstance);
    }
    
    this.activate = function() {
      var relTime = ET.currentTime - E.start;
      E.render.addClass("active-event");
      handler.activate(relTime);
    }

    this.deactivate = function() {
      var relTime = ET.lastActivation - E.start;
      handler.deactivate(relTime);
      if (ET.currentTime > E.end || ET.currentTime < E.start) {
        E.finish();
      }
    }

    this.finish = function() {
      E.render.removeClass("active-event");
      handler.finish();
    }
  }

  var e = new Event();
  for (var t = e.start; t <= e.end; t++) {
    if (!ET.events[t]) {
      ET.events[t] = [];
    }
    ET.events[t].push(e);
  }

  // todo: trigger redraw for dynamic events?
}
