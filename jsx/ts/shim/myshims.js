Array.prototype.forEach = function(cb) {
    for (var i = 0; i < this.length; i++) {
        cb(this[i]);
    }
};