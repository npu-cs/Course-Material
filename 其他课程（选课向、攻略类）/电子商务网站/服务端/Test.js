const fs = require('fs')
let express = require('express');
let bodyParser = require("body-parser");
let http = require("http");
let app = express();
let URL = require('url')

// 生成token标识
const jwt = require('jsonwebtoken');
const secret = require('./secret');

const cors = require('cors')
app.use(cors())

const path = require('path')
app.use(express.static(path.join(__dirname, 'public')))

//解析Body中的数据
app.use(bodyParser.urlencoded({
    extended: false
}));

//解析上传的JSON对象，
app.use(bodyParser.json())

let procdut_data = 
[
    {
        id: 1,
        name: 'AirPods',
        brand: 'Apple',
        image: 'http://127.0.0.1:8089/shopping/image?img=1.jpg',
        sales: 10000,
        cost: 1288,
        color: '白色'
    },
    {
        id: 2,
        name: 'BeatsX 入耳式耳机',
        brand: 'Beats',
        image: 'http://127.0.0.1:8089/shopping/image?img=2.jpg',
        sales: 11000,
        cost: 1188,
        color: '黑色'
    },
    {
        id: 3,
        name: 'Beats Solo3 Wireless 头戴式式耳机',
        brand: 'Beats',
        image: 'http://127.0.0.1:8089/shopping/image?img=3.jpg',
        sales: 5000,
        cost: 2288,
        color: '红色'
    },
    {
        id: 4,
        name: 'Beats Pill+ 便携式扬声器',
        brand: 'Beats',
        image: 'http://127.0.0.1:8089/shopping/image?img=4.jpg',
        sales: 3000,
        cost: 1888,
        color: '红色'
    },
    {
        id: 5,
        name: 'Sonos PLAY:1 无线扬声器',
        brand: 'Sonos',
        image: 'http://127.0.0.1:8089/shopping/image?img=5.jpg',
        sales: 8000,
        cost: 1578,
        color: '白色'
    },
    {
        id: 6,
        name: 'Powerbeats3 by Dr. Dre Wireless 入耳式耳机',
        brand: 'Beats',
        image: 'http://127.0.0.1:8089/shopping/image?img=6.jpg',
        sales: 12000,
        cost: 1488,
        color: '金色'
    },
    {
        id: 7,
        name: 'Beats EP 头戴式耳机',
        brand: 'Beats',
        image: 'http://127.0.0.1:8089/shopping/image?img=7.jpg',
        sales: 25000,
        cost: 788,
        color: '蓝色'
    },
    {
        id: 8,
        name: 'B&O PLAY BeoPlay A1 便携式蓝牙扬声器',
        brand: 'B&O',
        image: 'http://127.0.0.1:8089/shopping/image?img=8.jpg',
        sales: 15000,
        cost: 1898,
        color: '黑色'
    },
    {
        id: 9,
        name: 'Bose® QuietComfort® 35 无线耳机',
        brand: 'Bose',
        image: 'http://127.0.0.1:8089/shopping/image?img=9.jpg',
        sales: 14000,
        cost: 2878,
        color: '黑色'
    },
    {
        id: 10,
        name: 'B&O PLAY Beoplay H4 无线头戴式耳机',
        brand: 'B&O',
        image: 'http://127.0.0.1:8089/shopping/image?img=10.jpg',
        sales: 9000,
        cost: 2298,
        color: '肉色'
    }
]

/////////////////////////
//登录接口
app.get('/shopping/login', function (req, res) {
    let user = req.query.user;
    let pwd = req.query.pwd;
    // 查询数据库--省略
    const token = jwt.sign({ user, id: 123 }, secret.secretKey, { expiresIn: 20 })
    res.send({
        info: 'success',
        status: 200,
        token
    })
})

/////////////////////////
//获取产品信息
app.get('/shopping/product_data', function (req, res) {
    console.log("/shopping/product_data..........")

    res.status(200); //返回的状态码
//    console.log(procdut_data)
    res.send(JSON.stringify(procdut_data));
});

/////////////////////////
//获取图片
app.get('/shopping/image', function (req, res) {
    let arg = URL.parse(req.url, true).query
    console.log("/shopping/image.........."+path.join(__dirname,"image/"+arg.img))

    res.sendFile(path.join(__dirname,"image/"+arg.img))
});


////////////////////////
/*
app.post('/api/PDA/Login', function (req, res) {
    console.log('/api/PDA/Login')
    console.log(req.body)

    res.status(200); //返回的状态码
    respond_data = {
        data: JSON.stringify({
            deviceid:"",
            isSuccess:1,
            retMsg:"登录成功。"
        }),
        message: "",
        statusCode: 0,
        success: true
    }   
    res.send(JSON.stringify(respond_data));
});

*/
///////////////////////////
app.all('*', function(req, res, next) {
    console.log('app.all............')
    res.header("Access-Control-Allow-Origin", "*");
    res.header("Access-Control-Allow-Headers", "Content-Type,Content-Length, Authorization, Accept,X-Requested-With");
    res.header("Access-Control-Allow-Methods","PUT,POST,GET,DELETE,OPTIONS");
    res.header("X-Powered-By",' 3.2.1')
    if(req.method=="OPTIONS") res.send(200);/*让options请求快速返回*/
    else  next();
});

let server = app.listen(8089, function () {
    let host = server.address().address;
    let port = server.address().port;

    console.log('Mobile Commerce System is listening at http://%s:%s', host, port);
});
