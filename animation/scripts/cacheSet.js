function CacheSet(id) {
  this.id = id;
  this.blocks = [];
}
CacheSet.prototype.addBlock = function(block) {
  this.blocks.push(block);
}
CacheSet.prototype.buildDOM = function() {
  this.dom = $("<div>");
  this.dom.addClass("cache-set-container");
  this.blocksDom = $("<div>");
  this.blocksDom.addClass("blocks");
  this.dom.append(this.blocksDom);
  var label = $("<div>");
  label.addClass("set-label");
  label.text("Set " + this.id + ": ");
  this.dom.prepend(label);
  this.showInitialState();
}

CacheSet.prototype.clearDOM = function() {
  var S = this;
  if (S.blocksBuilt) {
    for (var i = 0; i < this.blocks.length; i++) {
      this.blocks[i].clearDOM();
    }
    S.blocksBuilt = false;
  }
  this.dom.remove();
}

CacheSet.prototype.showInitialState = function() {
  var S = this;
  this.dom.addClass("set-closed");
  this.dom.removeClass("set-open");
  this.dom.height( 5 * this.blocks.length);

  if (S.blocksBuilt) {
    for (var i = 0; i < this.blocks.length; i++) {
      this.blocks[i].clearDOM();
    }
    S.blocksBuilt = false;
  }

  $(S.dom).width("");

  this.dom.unbind("click");
  this.dom.on("click", function() {
    S.showOpenState();
    return false;
  });
}

CacheSet.prototype.setWidth = function() {
  var S = this;
  var width = 0;
  // build a dummy block to get size
  if (!S.blocksBuilt) {
    this.blocks[0].buildDOM();
    this.blocksDom.append(this.blocks[0].dom);
  }
  width += S.dom.find(".valid-bits:first").outerWidth(true);
  width += S.dom.find(".tag-bits:first").outerWidth(true);
  width += S.dom.find(".data-bits:first").outerWidth(true);
  $(S.dom).width(width);
  // remove dummy block
  if (!S.blocksBuilt) {
    this.blocks[0].clearDOM();
    this.blocks[0].dom.remove();
  }
}

CacheSet.prototype.showOpenState = function() {
  var S = this;
  this.dom.addClass("set-open");
  this.dom.removeClass("set-closed");
  this.dom.height("");
  
  if (!S.blocksBuilt) {
    for (var i = 0; i < this.blocks.length; i++) {
      this.blocks[i].buildDOM();
      this.blocksDom.append(this.blocks[i].dom);
    }
    S.blocksBuilt = true;
  }

  this.setWidth();

  this.dom.unbind("click");
  this.dom.on("click", function() {
    S.showInitialState();
    return false;
  });
}
