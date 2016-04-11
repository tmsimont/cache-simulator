function CacheSet(id) {
  this.blocks = [];
  this.dom = $("<div>");
  this.dom.addClass("cache-set-container");
  this.blocksDom = $("<div>");
  this.blocksDom.addClass("blocks");
  this.dom.append(this.blocksDom);
  var label = $("<div>");
  label.addClass("set-label");
  label.text("Set " + id + ": ");
  this.dom.prepend(label);
}
CacheSet.prototype.addBlock = function(block) {
  this.blocks.push(block);
  this.blocksDom.append(block.dom);
}

