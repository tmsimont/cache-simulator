var EventAnimations = {};

EventAnimations[CACHE_EVENT.SEARCH] = function(cacheEvent) {
  var architecture = cacheEvent.architecture;
  var cache = architecture.caches[cacheEvent.cacheID];
  var set = cache.sets[cacheEvent.cacheSet];
  var block = set.blocks[cacheEvent.blockId];

  var line = false;
  var showingAddress = false;
  var scrolledToCache = false;
  var scrolledToCacheSet = false;
  var setOpen = false;

  this.activate = function(time) {
    switch (time) {
      case 4:
        set.dom.find(".tag-bit").addClass("flash-search");
        cache.addressElement.find(".tag").addClass("tag-search");
      case 3:
        if (!setOpen) {
          line.remove();
          set.showOpenState();
          if (!scrolledToCacheSet) {
            $(set.dom).velocity("scroll", {
              container : $("#stage"),
              duration : 200,
              offset : -30
            });
            scrolledToCache = true;
          }
          line = cache.lineToSet(set);
          setOpen = true;
        }
      case 2:
        if (!line) {
          line = cache.lineToSet(set);
        }
      case 1:
        if (!showingAddress) {
          cache.showAddress(cacheEvent.address);
          showingAddress = true;
        }
      case 0:
        cache.showOpenState();
        if (!scrolledToCache) {
          $(cache.dom).velocity("scroll", {
            container : $("#stage"),
            duration : 200,
            offset : -1 * (cache.label.outerHeight() + 5)
          });
          scrolledToCache = true;
        }
        break;
    }
  }
  this.deactivate = function(time) {
  }
  this.finish = function() {
    if (line) {
      line.remove();
      line = false;
    }
    if (showingAddress) {
      cache.clearAddress();
      showingAddress = false;
    }
    scrolledToCacheSet = false;
    scrolledToCache = false;
    set.dom.find(".tag-bit").removeClass("flash-search");
    cache.addressElement.find(".tag").removeClass("tag-search");
    if (setOpen) {
      set.showInitialState();
      setOpen = false;
    }
  }
}

EventAnimations[CACHE_EVENT.HIT] = function(cacheEvent) {
  var architecture = cacheEvent.architecture;
  var cache = architecture.caches[cacheEvent.cacheID];
  var set = cache.sets[cacheEvent.cacheSet];
  var block = set.blocks[cacheEvent.blockId];

  var line = false;
  var bitLine = false;
  var showingAddress = false;
  var scrolledToCache = false;
  var setOpen = false;

  this.activate = function(time) {
    switch (time) {
      case 1:
        if(!bitLine) {
          var hitBit = 1 + cache.getOffset(cacheEvent.address);
          var bit = $(block.dom).find( ".data-bit:nth-child("+hitBit+")")
          bit.addClass("hit-bit");
          bitLine = cache.lineToBit(bit);
        }
        set.dom.find(".tag-bit").removeClass("flash-search");
        cache.addressElement.find(".tag").removeClass("tag-search");
        break;
      case 0:
        if (!setOpen) {
          set.showOpenState();  
          setOpen = true;
        }
        if (!showingAddress) {
          cache.showAddress(cacheEvent.address);
          showingAddress = true;
        }
        if (!line) {
          line = cache.lineToSet(set);
        }
        set.dom.find(".tag-bit").addClass("flash-search");
        cache.addressElement.find(".tag").addClass("tag-search");
        cache.showOpenState();
        if (!scrolledToCache) {
          $(cache.dom).velocity("scroll", {
            container : $("#stage"),
            duration : 200,
            offset : -1 * (cache.label.outerHeight() + 5)
          });
          scrolledToCache = true;
        }
        block.dom.find(".tag-bit").addClass("flash-hit");
        break;
    }
  }

  this.deactivate = function(time) {
  }

  this.finish = function() {
    if (line) {
      line.remove();
      line = false;
    }
    if (bitLine) {
      bitLine.remove();
      bitLine = false;
    }
    if (showingAddress) {
      cache.clearAddress();
      showingAddress = false;
    }
    scrolledToCache = false;
    set.dom.find(".tag-bit").removeClass("flash-search");
    block.dom.find(".tag-bit").removeClass("flash-hit");
    set.dom.find(".hit-bit").removeClass("hit-bit");
    if (setOpen) {
      set.showInitialState();
      setOpen = false;
    }
  }
}


EventAnimations[CACHE_EVENT.MISS] = function(cacheEvent) {
  var architecture = cacheEvent.architecture;
  var cache = architecture.caches[cacheEvent.cacheID];
  var set = cache.sets[cacheEvent.cacheSet];
  var block = set.blocks[cacheEvent.blockId];

  var line = false;
  var showingAddress = false;
  var scrolledToCache = false;
  var setOpen = false;

  this.activate = function(time) {
    switch (time) {
      case 1:
        set.dom.find(".tag-bit").removeClass("flash-miss");
        break;
      case 0:
        if (!setOpen) {
          set.showOpenState();  
          setOpen = true;
        }
        if (!showingAddress) {
          cache.showAddress(cacheEvent.address);
          showingAddress = true;
        }
        if (!line) {
          line = cache.lineToSet(set);
        }
        cache.showOpenState();
        if (!scrolledToCache) {
          $(cache.dom).velocity("scroll", {
            container : $("#stage"),
            duration : 200,
            offset : -1 * (cache.label.outerHeight() + 5)
          });
          scrolledToCache = true;
        }
        set.dom.find(".tag-bit").addClass("flash-miss");
        break;
    }
  }

  this.deactivate = function(time) {
  }

  this.finish = function() {
    if (line) {
      line.remove();
      line = false;
    }
    if (showingAddress) {
      cache.clearAddress();
      showingAddress = false;
    }
    scrolledToCache = false;
    set.dom.find(".tag-bit").removeClass("flash-search");
    block.dom.find(".tag-bit").removeClass("flash-miss");
    if (setOpen) {
      set.showInitialState();
      setOpen = false;
    }
  }
}


