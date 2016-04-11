function Cache(parameters) {
  this.sets = [];
  this.parameters = parameters;

  this.dom = $("<div>");
  this.dom.addClass("cache");
  this.onStageBuilt = function() {
  }
}
Cache.prototype.addSet = function(set) {
  this.sets.push(set);
  this.dom.append(set.dom);
}

