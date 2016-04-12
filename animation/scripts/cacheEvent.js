var CACHE_EVENT_HIT  = 0;
var CACHE_EVENT_MISS = 1;

function CacheEvent(ca, params) {
  this.ca = ca;
  this.params = params;
  this.animate = function() {
    EventAnimations[params.type](this);
  }
}

var EventAnimations = {};
EventAnimations[CACHE_EVENT_HIT] = function(cacheEvent) {
  // 1: show the search
  
  // new event, address to read...
  var address = new CacheAddress();
  var addrView = addressView(address);
  $("#stage").prepend(addrView);

  CacheSearch({
    address : address,
    cache   : cacheEvent.ca.caches[cacheEvent.params.cacheID],
    set     : cacheEvent.ca.caches[cacheEvent.params.cacheID]
               .sets[cacheEvent.params.cacheSet],
    block   : cacheEvent.ca.caches[cacheEvent.params.cacheID]
               .sets[cacheEvent.params.cacheSet]
               .blocks[cacheEvent.params.blockId]
  });

  // 2: show the hit
}
