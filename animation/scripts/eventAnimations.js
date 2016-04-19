var EventAnimations = {};

EventAnimations[CACHE_EVENT.SEARCH] = function(cacheEvent) {
  var architecture = cacheEvent.architecture;
  var cache = architecture.caches[cacheEvent.cacheID];
  var set = cache.sets[cacheEvent.cacheSetID];
  var block = set.blocks[cacheEvent.blockID];

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
          if (line) {
            line.remove();
            line = false;
          }
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
    switch (time) {
      case 2:
        if (line) {
          line.remove();
          line = false;
        }
        break;
      default:
        break;
    }
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
  var set = cache.sets[cacheEvent.cacheSetID];
  var block = set.blocks[cacheEvent.blockID];

  var line = false;
  var bitLine = false;
  var showingAddress = false;
  var scrolledToCache = false;
  var setOpen = false;
  var scrollToShowOffset = false;

  this.activate = function(time) {
    switch (time) {
      case 6:
      case 5:
      case 4:
      case 3:
        if (!scrollToShowOffset) {
          $(set.dom).velocity("scroll", {
            container : $("#stage"),
            duration : 200,
            offset : -1 * (cache.label.outerHeight() + 5)
          });
          scrollToShowOffset = true;
        }
      case 2:
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
        cache.showOpenState();
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
    if (time == 2) {
      if (bitLine) {
        bitLine.remove();
        bitLine = false;
        var hitBit = 1 + cache.getOffset(cacheEvent.address);
        var bit = $(block.dom).find( ".data-bit:nth-child("+hitBit+")")
        bit.removeClass("hit-bit");
      }
    }
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

EventAnimations[CACHE_EVENT.HIT_VALID] = function(cacheEvent) {
  var normalHitAnimator = new EventAnimations[CACHE_EVENT.HIT](cacheEvent);
  var architecture = cacheEvent.architecture;
  var cache = architecture.caches[cacheEvent.cacheID];
  var set = cache.sets[cacheEvent.cacheSetID];
  var block = set.blocks[cacheEvent.blockID];

  this.activate = function(time) {
    switch (time) {
      case 2:
        normalHitAnimator.activate(time);
      case 1:
        block.dom.find(".valid-bit").addClass("valid");
      default:
        normalHitAnimator.activate(time);
        break;
    }
  }
  this.deactivate = function(time) {
    normalHitAnimator.deactivate(time);
    if (time == 1) {
      block.dom.find(".valid-bit").removeClass("valid");
    }
  }
  this.finish = function(time) {
    block.dom.find(".valid-bit").removeClass("valid");
    normalHitAnimator.finish(time);
  }
}

EventAnimations[CACHE_EVENT.HIT_INVALID] = function(cacheEvent) {
  var normalHitAnimator = new EventAnimations[CACHE_EVENT.HIT](cacheEvent);
  var architecture = cacheEvent.architecture;
  var cache = architecture.caches[cacheEvent.cacheID];
  var set = cache.sets[cacheEvent.cacheSetID];
  var block = set.blocks[cacheEvent.blockID];

  this.activate = function(time) {
    if (time >= 1) {
      block.dom.find(".valid-bit").addClass("invalid");
    }
    else if (time < 1) {
      normalHitAnimator.activate(time);
    }
  }
  this.deactivate = function(time) {
    normalHitAnimator.deactivate(time);
    if (time == 1) {
      block.dom.find(".valid-bit").removeClass("invalid");
    }
  }
  this.finish = function(time) {
    block.dom.find(".valid-bit").removeClass("invalid");
    normalHitAnimator.finish(time);
  }
}

EventAnimations[CACHE_EVENT.MISS] = function(cacheEvent) {
  var architecture = cacheEvent.architecture;
  var cache = architecture.caches[cacheEvent.cacheID];
  var set = cache.sets[cacheEvent.cacheSetID];
  var block = set.blocks[cacheEvent.blockID];

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
        cache.showOpenState();
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


EventAnimations[CACHE_EVENT.REPLACE] = function(cacheEvent){ 
  var architecture = cacheEvent.architecture;
  var cache = architecture.caches[cacheEvent.cacheID];
  var set = cache.sets[cacheEvent.cacheSetID];
  var block = set.blocks[cacheEvent.blockID];
  var toCache = architecture.caches[cacheEvent.toCacheID];
  var toSet = toCache.sets[cacheEvent.toCacheSetID];
  var toBlock = toSet.blocks[cacheEvent.toBlockID];


  var bitLine = false;
  var setOpen = false;
  var showingAddress = false;
  var line = false;
  var scrolledToCache = false;

  var lineForMotion = false;
  var lineR = false;
  var scrolledToToCache = false;

  var showingToAddress = false;

  this.activate = function (time) {
    switch (time) {
      case 6:
        toBlock.dom.addClass("moving-block");
      case 5:
        if (!showingToAddress) {
          toCache.showAddress(cacheEvent.address);
          showingToAddress = true;
        }
      case 4:
        toSet.showOpenState();
        // update lines now that upper set is open
        lineForMotion.remove();
        lineForMotion = cache.lineSendBlockTo(block, toCache);
        lineR.remove();
        lineR = toCache.lineToSet(toSet);
      case 3: 
        if (!lineR) {
          lineR = toCache.lineToSet(toSet);
        }
      case 2:
        if (!scrolledToToCache) {
          $(toCache.dom).velocity("scroll", {
            container : $("#stage"),
            duration : 200,
            offset : -1 * (cache.label.outerHeight() + 5)
          });
          scrolledToCache = true;
        }
  
      case 1:
        toCache.showOpenState();
        if(!lineForMotion) {
          lineForMotion = cache.lineSendBlockTo(block, toCache);
        }


      case 0:
        // show state where block was found
        // ----------------------------------------
        cache.showOpenState();
        if (!setOpen) {
          set.showOpenState();  
          setOpen = true;
        }
        if (!showingAddress) {
          cache.showAddress(cacheEvent.address);
          showingAddress = true;
        }
        if (!scrolledToCache) {
          $(cache.dom).velocity("scroll", {
            container : $("#stage"),
            duration : 200,
            offset : -1 * (cache.label.outerHeight() + 5)
          });
          scrolledToCache = true;
        }
        // ----------------------------------------

        // now do new stuff
        block.dom.addClass("moving-block");
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
    block.dom.removeClass("moving-block");
    toBlock.dom.removeClass("moving-block");
    if (setOpen) {
      set.showInitialState();
      setOpen = false;
    }
    if (lineForMotion) {
      lineForMotion.remove();
      lineForMotion = false;
    }
    if (lineR) {
      lineR.remove();
      lineR = false;
    }
  }

  
}


