import axios from 'axios'

//axios.defaults.withCredentials = true;

// 将 token 放到拦截器里面处理
//axios.interceptors.request.use(function (config) {
//    config.headers['authorization'] = requestToken; // 将 token 放到 header 里面
//    return config;
//});
/*
axios.interceptors.response.use(
    (res) => res,
    (err) => {
        err.status = 500
        err.data = ""
        console.log(JSON.stringify(err))
        return err
    }
);
*/
let svrHost = ""
let baseURL = "";

//获取服务端地址
export function SetSrvHost() {
    let host = window.location.href
    let url = host.split('/')
    let ip = url[2].split(':')
    svrHost = url[0] + "//" + ip[0] +":8089"
    baseURL = svrHost + "/shopping/"
    // http://localhost:8089/shopping/
}

export function get_product_data(callback) {
    console.log(baseURL + "product_data")
    axios.get(baseURL + "product_data").then(response => {
        callback(response.data)
    })
}

export function get_login_token(params) {
    return axios.get(baseURL + "login", {
        params
    })
}

/*
export function SavePage(type, group, name, page) {
    let url = "page?type=" + type + "&group=" + group + "&name=" + name
    axios.post(baseURL + url, page).then(response => {
    })
}

//<<2021-05-27
export function CreatePage(type, group, name, dept, account, callback) {
    let url = "page?type=" + type + "&group=" + group + "&name=" + name + "&dept=" + dept + "&account=" + account
    axios.put(baseURL + url).then(response => {
        callback(response.data)
    })
}
//2021-05-27 >>

export function DeletePage(type, group, name, callback) {
    let url = "page?type=" + type + "&group=" + group + "&name=" + name
    axios.delete(baseURL + url).then(response => {
        callback(response.data)
    })
}
*/