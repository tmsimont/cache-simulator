function Cache(parameters) {
  this.sets = [];
  this.parameters = parameters;

  this.dom = $("<div>");
  this.dom.addClass("cache");

  this.label = $("<div>");
  this.label.addClass("cache-label");
  this.label.text(parameters.name);
  this.dom.append(this.label);

  this.cacheSetsContainer = $("<div>");
  this.cacheSetsContainer.addClass("cache-sets-container");
  this.dom.append(this.cacheSetsContainer);


  this.showInitialState();

  this.onStageBuilt = function() {
  }
}

Cache.prototype.addSet = function(set) {
  this.sets.push(set);
  this.cacheSetsContainer.append(set.dom);
}

Cache.prototype.showInitialState = function() {
  var C = this;
  C.dom.addClass("state-initial");
  C.dom.removeClass("state-open");

  // width and height based on cache size params
  this.dom.width(1.5 * C.parameters.size);
  this.dom.height(1.5 * C.parameters.size/3);

  // click is re-bound
  C.dom.unbind("click");
  C.dom.on("click", function() {
    C.showOpenState();
  });
}

Cache.prototype.showOpenState = function() {
  var C = this;
  C.dom.addClass("state-open");
  C.dom.removeClass("state-initial");

  // free width and height
  C.dom.height("");
  C.dom.width("");

  // click is re-bound
  C.dom.unbind("click");
  C.dom.on("click", function() {
    C.showInitialState();
  });
}


Cache.prototype.getIndexBits = function(address) {
  return address.bits.slice(9,10);
}

Cache.prototype.getTagBits = function(address) {
  return address.bits.slice(0, 8);
}

Cache.prototype.getOffsetBits = function(address) {
  return address.bits.slice(11,24);
}

