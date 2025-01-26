import Vue from 'vue';
import VueRouter from 'vue-router';
import Routers from './router';
import Vuex from 'vuex';
import App from './app.vue';
import './style.css';
import ElementUI from 'element-ui';
import 'element-ui/lib/theme-chalk/index.css';

//import product_data from './product';

let product_data = [];

Vue.use(VueRouter);
Vue.use(Vuex);
Vue.use(ElementUI);

// 数组排重
function getFilterArray (array) {
    const res = [];
    const json = {};
    for (let i = 0; i < array.length; i++){
        const _self = array[i];
        if(!json[_self]){
            res.push(_self);
            json[_self] = 1;
        }
    }
    return res;
}
//////////////////////////////////////////////////////////
//新增
function Callback(product) {
    product_data = product;
}
/////////////////////////////////////////////////////////

const store = new Vuex.Store({
    state: {
        productList: [],
        cartList: [],
        userinfo: {
            username: '',
            token: null,
        }
    },
    getters: {
        brands: state => {
            const brands = state.productList.map(item => item.brand);
            return getFilterArray(brands);
        },
        colors: state => {
            const colors = state.productList.map(item => item.color);
            return getFilterArray(colors);
        }
    },
    mutations: {
        // 添加商品列表
        setProductList (state, data) {
            state.productList = data;
        },
        // 添加到购物车
        addCart (state, id) {
            // 先判断购物车是否已有，如果有，数量+1
            const isAdded = state.cartList.find(item => item.id === id);
            if (isAdded) {
                isAdded.count ++;
            } else {
                state.cartList.push({
                    id: id,
                    count: 1
                })
            }
        },
        // 修改商品数量
        editCartCount (state, payload) {
            const product = state.cartList.find(item => item.id === payload.id);
            product.count += payload.count;
        },
        // 删除商品
        deleteCart (state, id) {
            const index = state.cartList.findIndex(item => item.id === id);
            state.cartList.splice(index, 1);
        },
        // 清空购物车
        emptyCart (state) {
            state.cartList = [];
        },
        // 设置token
        setUser(state, payload) {
            state.userinfo = payload;
        },
        // 清空用户信息
        clearUser(state) {
            state.cartList = [];
            state.userinfo = {
                username: '',
                token: null,
            }
        },

    },
    actions: {
        // 请求商品列表
        getProductList (context) {
//////////////////////////////////////////////////////////
//新增
            let request = require("./request.js");
            request.SetSrvHost();
            // 真实环境通过 ajax 获取，这里用异步模拟
            request.get_product_data(Callback)
////////////////////////////////////////////////////////////
            setTimeout(() => {
                context.commit('setProductList', product_data);
            }, 500);
        },
        // 购买
        buy (context) {
            // 真实环境应通过 ajax 提交购买请求后再清空购物列表
            return new Promise(resolve=> {
                setTimeout(() => {
                    context.commit('emptyCart');
                    resolve();
                }, 500)
            });
        }
    }
});

let userinfo = sessionStorage.getItem('userinfo')
if (userinfo) {
    userinfo = JSON.parse(userinfo);
    store.commit('setUser',userinfo)
}

// 路由配置
const RouterConfig = {
    // 使用 HTML5 的 History 路由模式
    mode: 'history',
    routes: Routers
};
const router = new VueRouter(RouterConfig);

router.beforeEach((to, from, next) => {
    if (to.meta.isLogin) {
        let token = store.state.userinfo.token;
        console.log(token)
        if (token) {
            next()
        } else {
            next('/login')
        }
    } else {
        next()
    }
    window.document.title = to.meta.title;
});

router.afterEach((to, from, next) => {
    window.scrollTo(0, 0);
});

new Vue({
    el: '#app',
    router: router,
    store: store,
    render: h => {
        return h(App)
    }
});