function Cache(parameters) {
  this.sets = [];
  this.parameters = parameters;

  this.indexSize = Math.log2(parameters.associativity);
  this.offsetSize = Math.log2(parameters.blockSize);
  this.tagSize = parameters.addressSize - this.indexSize - this.offsetSize;

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

}

Cache.prototype.addSet = function(set) {
  this.sets.push(set);
}

Cache.prototype.showInitialState = function() {
  var C = this;

  C.dom.addClass("state-initial");
  C.dom.removeClass("state-open");

  if (C.setsBuilt) {
    for (var i = 0; i < C.sets.length; i++) {
      C.sets[i].clearDOM();
    }
    C.setsBuilt = false;
  }

  if(C.addressShowing) {
    C.addressElement.remove();
    C.addressShowing = false;
  }

  // width based on cache size params
  this.dom.width(.25 * C.parameters.size);
  this.dom.height(.05 * C.parameters.size);

  // click is re-bound
  C.dom.unbind("click");
  C.dom.on("click", function() {
    C.showOpenState();
  });
}

Cache.prototype.clearAddress = function() {
  var C = this;
  var dummyBits = "";
  for (var i = 0; i < C.parameters.addressSize; i++) {
    dummyBits += "x";
  }
  C.showAddress(dummyBits);
}

Cache.prototype.showAddress = function(addressBits) {
  var C = this;
  if (C.addressShowing) {
    C.addressElement.remove();
  }
  var addr = new CacheAddress(C, addressBits);
  C.address = addr;
  C.addressElement = addr.dom;
  C.dom.prepend(C.addressElement);
  C.addressShowing = true;
}


Cache.prototype.showOpenState = function() {
  var C = this;

  C.dom.addClass("state-open");
  C.dom.removeClass("state-initial");

  if(!C.addressShowing) {
    var dummyBits = "";
    for (var i = 0; i < C.parameters.addressSize; i++) {
      dummyBits += "x";
    }
    C.showAddress(dummyBits);
  }

  // free width
  C.dom.width("");
  C.dom.height("");

  if (!C.setsBuilt) { 
    for (var i = 0; i < C.sets.length; i++) {
      C.sets[i].buildDOM();
      C.cacheSetsContainer.append(C.sets[i].dom);
      var left = (C.addressElement.outerWidth(true) + 20);
      $(C.sets[i].dom).css({
        "left":  left + "px",
      });
      C.sets[i].setWidth();
    }
    C.setsBuilt = true;
  }


  // click is re-bound
  C.dom.unbind("click");
  C.dom.on("click", function() {
    C.showInitialState();
  });
}

Cache.prototype.getIndexBits = function(addressBits) {
  return addressBits.slice(
    this.tagSize, this.tagSize + this.indexSize
  );
}
Cache.prototype.getIndex = function(addressBits) {
  return parseInt(this.getIndexBits(addressBits), 2)
}

Cache.prototype.getTagBits = function(addressBits) {
  return addressBits.slice(0, this.tagSize);
}
Cache.prototype.getTag = function(addressBits) {
  return parseInt(this.getTagBits(addressBits), 2)
}

Cache.prototype.getOffsetBits = function(addressBits) {
  return addressBits.slice(
    this.tagSize + this.indexSize,
    this.addressSize
  );
}
Cache.prototype.getOffset = function(addressBits) {
  return parseInt(this.getOffsetBits(addressBits), 2)
}

Cache.prototype.lineToSet = function(set) {
  var C = this;
  var idxp = $(C.addressElement).find(".values .idx").position();
  var target = set.dom;
  var csp = target.position();
  var targetY = csp.top + target.height() / 2;
  var targetX = csp.left - 20;
  return new drawArrow(
      {
        x:idxp.left + 10, 
        y:idxp.top + 20
      }, 
      {
        x:targetX,
        y:targetY
      },
      [
        {
          x:idxp.left + 10,
          y:targetY
        }
      ],
      C.dom
  );

}


Cache.prototype.lineToBit = function(bit) {
  var C = this;
  var offsetE = $(C.addressElement).find(".values .offset");
  var offsetP = offsetE.position();
  console.log(bit);
  var target = bit;
  var csp = target.position();
  var pp = target.offsetParent().position();
  var targetY = (pp.top + csp.top) - bit.outerHeight();
  var targetX = (pp.left + csp.left) + (bit.outerWidth());
  return new drawArrow(
      {
        x:offsetP.left + offsetE.outerWidth(), 
        y:offsetP.top - offsetE.outerHeight() / 2
      }, 
      {
        x:targetX,
        y:targetY
      },
      [
        {
          x:targetX - 10,
          y:offsetP.top - offsetE.outerHeight() / 2
        }
      ],
      C.dom
  );

}
