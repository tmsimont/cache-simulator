function CacheParameters() {
  this.priority = 0;
  this.blockSize = 32;
  this.name = "L1";
  this.size = 64 * 8;
  this.addressSize = 32;
  this.associativity = 2;
  this.hasWriteBuffer = false;
  this.hasVictimBuffer = false;
  this.replacementPolicy = 0;
  this.missPenalty = 10;
  this.hitTime = 2;
}

