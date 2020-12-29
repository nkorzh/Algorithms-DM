"use strict";

      function escape(str) {
        return str.replace(/&/g,'&amp;').replace(/</g,'&lt;').replace(/>/g,'&gt;') ;
    }

    var logArea = document.getElementById("out");

    function println() {
        print.apply(null, arguments);
        logArea.innerHTML += "\n";
    }

    function print() {
        const line = Array.prototype.map.call(arguments, String).join(' ');
        console.log(line);
        logArea.innerHTML += escape(line);
    }

    function LoggerProto(writer, messageProcessor) {
        this.writer = writer;
        this.processMessage = messageProcessor === undefined ?
            (mes => mes) : messageProcessor;
        this.allowedMessageType = 0;
    }
    LoggerProto.prototype.UrgencyType = {
        All: 0,
        Info: 1,
        Debug: 2,
        Warning: 3,
        Error: 4
    };
    LoggerProto.prototype.filterByUrgency = function(type) {
        this.allowedMessageType = this.UrgencyType[type];
    };
    LoggerProto.prototype.log = function(message, type = 0) {
        if (this.allowedMessageType === this.UrgencyType.All ||
                this.UrgencyType[type] >= this.allowedMessageType)
            this.writer(this.processMessage(message));
    };
    LoggerProto.prototype.changeMessageProcessor = function (newProcessor) {
        this.processMessage = newProcessor === undefined ?
            (mes => mes) : newProcessor;
    };
    /*
     * По заданию ConsoleLogger обязан использовать println;
     * в примерах print, используемый в println печатает
     * сообщение и в консоль, и в HTML файл
     */
    function ConsoleLogger(processMessage) {
        LoggerProto.call(this, println, processMessage);
    }
    ConsoleLogger.prototype = Object.create(LoggerProto.prototype);

    function HTMLLogger(processMessage) {
        LoggerProto.call(this,
            function (message) {
                logArea.innerHTML += escape(message) + "\n";
            }, processMessage);
    }
    HTMLLogger.prototype = Object.create(LoggerProto.prototype);

    function CompositeLogger(...loggers) {
        this.loggers = loggers;
    }

    CompositeLogger.prototype.log = function(message) {
        this.loggers.forEach(function(logger) {
            logger.log(message);
        });
    };
    CompositeLogger.prototype.setFilterById = function (id, filter) {
        this.loggers[id].filterByUrgency(filter);
    };
    CompositeLogger.prototype.setFormatById = function (id, processor) {
        this.loggers[id].changeMessageProcessor(processor);
    };

    function InsertDate(mes) {
        let d = new Date();
        let options = {
            era: 'long',
            year: 'numeric',
            month: 'long',
            day: 'numeric',
            weekday: 'long',
            timezone: 'UTC',
            hour: 'numeric',
            minute: 'numeric',
            second: 'numeric'
        };
        return d.toLocaleDateString("en-US", options) + " >> " + mes.toString();
    }


    let a = new CompositeLogger(new HTMLLogger(), new ConsoleLogger());

    a.log("Printed to console and html!");
    a.setFilterById(1, "Debug");
    a.log("HTML only log !", "All");  // set filter by debug and higher
    a.setFormatById(0, InsertDate);
    a.log("Html only with date!");
