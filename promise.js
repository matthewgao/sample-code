var EventEmitter = require('events').EventEmitter;
var http = require('http');
var util = require('util');
// 定义promise对象
var Promise = function(){
    // 实现继承事件类
    EventEmitter.call(this);
}
// 继承事件通用方法
util.inherits(Promise, EventEmitter);
// then 方法为promise/A 规范中的方法
Promise.prototype.then1 = function(successHandler, errorHandler, progressHandler){
    if (typeof successHandler == 'function'){
        console.log("Here1");
        this.once('success', successHandler);
        console.log("Here2");
    }
    if (typeof errorHandler === 'function'){
        this.once('error', errorHandler);
    }
    if (typeof progressHandler === 'function'){
        this.on('process', progressHandler);
    }
    return this;
}
// 定义延迟对象
// 包含一个状态和一个promise对象
var Deferred = function(){
    // this.state = 'unfulfilled';
    this.promise = new Promise();
}
Deferred.prototype.resolve = function(obj){
    // this.state = 'fulfilled';
    this.promise.emit('success', obj);
}
Deferred.prototype.reject = function(err){
    // this.state = 'failed';
    this.promise.emit('error', err);
}
Deferred.prototype.progress = function(data){
    debugger;
    this.promise.emit('process', data);
}
// 利用一个http请求来运用上面定义的promise/deferred
var client = function(){
    var options = {
        hostname:'www.baidu.com',
        port:80,
        path:'/',
        method: 'get'
    };
    var deferred = new Deferred();
    var req = http.request(options, function(res){
        res.setEncoding('utf-8');
        var data = '';
        res.on('data', function(chunk){
            data += chunk;
            deferred.progress(chunk);
        });
        res.on('end', function(){
            deferred.resolve(data);
        });
    });
    req.on('error', function(err){
        deferred.reject(err);
    })
    // req.end();
    return deferred.promise;
}

var c = client();
console.log("Here");
c.then1(function(data){
    console.log('请求完成', data);
}, function(err){
    console.log('访问错误', err);
}, function(chunk){
    console.log('正在读取', chunk);
});
console.log("Here4");