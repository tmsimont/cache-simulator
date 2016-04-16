function CacheBlock(validBits, tagBits, contentBits) {
  this.validBits = validBits;
  this.tagBits = tagBits;
  this.contentBits = contentBits;
}

CacheBlock.prototype.buildDOM = function () {
  this.dom = $("<div>");
  this.dom.addClass("cache-block");
  this.valid = new BitGroup(this.validBits, "valid")
  this.dom.append(this.valid.dom);
  this.tag = new BitGroup(this.tagBits, "tag");
  this.dom.append(this.tag.dom);
  this.data = new BitGroup(this.contentBits, "data");
  this.dom.append(this.data.dom);
}

CacheBlock.prototype.clearDOM = function() {
  this.valid.dom.remove();
  this.tag.dom.remove();
  this.data.dom.remove();
  this.dom.remove();
}

function BitGroup(numBits, cssClass) {
  this.dom = $("<div>");
  this.dom.addClass("bit-group");
  this.dom.addClass(cssClass + "-bits");
  for (var k=0; k < numBits; k++) {
    var bit = $("<div>");
    bit.addClass("cache-bit");
    bit.addClass(cssClass + "-bit");
    this.dom.append(bit);
  }
}

