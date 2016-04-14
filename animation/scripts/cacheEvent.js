var CACHE_EVENT = {
  SEARCH       : 0,
  HIT          : 1,
  MISS         : 2
}

function CacheEvent(params) {
  var self = this;
  for (var i in params) {
    self[i] = params[i];
  }
  if (typeof params.animator == "undefined")
    self.animator = new EventAnimations[self.type](this);

  if (typeof params.activate == "undefined")
    self.activate = function(time) {
      self.animator.activate(time);
    }

  if (typeof params.deactivate == "undefined")
    self.deactivate = function(time) {
      self.animator.deactivate(time);
    }

  if (typeof params.finish == "undefined")
    self.finish = function() {
      self.animator.finish();
    }
}

