function CacheBlock(validBits, tagBits, contentBits) {
  this.dom = $("<div>");
  this.dom.addClass("cache-block");
  this.valid = new BitGroup(validBits.length, "valid")
  this.dom.append(this.valid.dom);
  this.tag = new BitGroup(tagBits.length, "tag");
  this.dom.append(this.tag.dom);
  this.data = new BitGroup(contentBits.length, "data");
  this.dom.append(this.data.dom);
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

