import VueRouter from "vue-router";

const routers = [
    {
        path: '/list',
        meta: {
            isLogin:true,
            title: '商品列表'
        },
        component: (resolve) => require(['./views/list.vue'], resolve)
    },
    {
        path: '/product/:id',
        meta: {
            isLogin: true,
            title: '商品详情'
        },
        component: (resolve) => require(['./views/product.vue'], resolve)
    },
    {
        path: '/cart',
        meta: {
            isLogin: true,
            title: '购物车'
        },
        component: (resolve) => require(['./views/cart.vue'], resolve)
    },
    {
        path: '/login',
        meta: {
            isLogin: false,
            title: '登录页面'
        },
        component: (resolve) => require(['./views/login.vue'], resolve)
    },
    {
        path: '*',
        redirect: '/list'
    }
];

export default routers;