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
  var numBlocks = parameters.size / parameters.blockSize;

  // number of sets 
  var numberOfSets = numBlocks / parameters.associativity;

  
  // build cache blocks and build into sets for cache
  for (var i = 0; i < numberOfSets; i++) {
    var set = new CacheSet(i);
    for (var j = 0; j < parameters.associativity; j++) {
      var block = new CacheBlock(
        1,
        cache.tagSize,
        parameters.blockSize
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
  }
}


CacheArchitecture.prototype.init = function() {
  // show initial state of elements
}
