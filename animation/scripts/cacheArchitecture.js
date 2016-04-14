function CacheArchitecture() {
  this.caches = [];
  this.dom = $("<div>");
  this.dom.addClass("cache-architecture");

  this.label = $("<div>");
  this.label.addClass("cache-architecture-label");
  this.label.text("Cache Architecture");
  this.dom.prepend(this.label);
}
CacheArchitecture.prototype.addCache = function(parameters) {
  var cache = new Cache(parameters);

  // figure number of lines
  var numLines = parameters.size / parameters.blockSize;

  // figure number of sets
  var linesPerSet = numLines / parameters.associativity;
  
  // build cache blocks and build into sets for cache
  for (var i = 0; i < parameters.associativity; i++) {
    var set = new CacheSet(i);
    for (var j = 0; j < linesPerSet; j++) {
      // todo: figure out number of bits needed for tag
      var block = new CacheBlock(
          [1],
          [0,1,0,1,1,1,0,1],
          [1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,1,0,1,1,0,1,0,0,0,0,1,1,0,1]
       );
      set.addBlock(block);
    }
    cache.addSet(set);
  }

  this.caches.push(cache);
  this.dom.append(cache.dom);
}
CacheArchitecture.prototype.adjustSizing = function() {
  for (var i = 0; i < this.caches.length; i++) {
    var dom = this.caches[i].dom;
    var width = 0;
    width += dom.find(".valid-bits:first").outerWidth(true);
    width += dom.find(".tag-bits:first").outerWidth(true);
    width += dom.find(".data-bits:first").outerWidth(true);
    $(dom).width(width);
  }
}


CacheArchitecture.prototype.init = function() {
  // show initial state of elements
}
