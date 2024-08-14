<template>
    <div>
        <div class="header">
            <router-link to="/list" class="header-title">移动电子商务网站</router-link>
            <div class="header-menu">
                <el-dropdown @command="handleUser">
                    <div class="header-title">
                        欢迎：{{ this.$store.state.userinfo.username }}
                        <i class="el-icon-arrow-down el-icon--right"></i>
                    </div>
                    <el-dropdown-menu slot="dropdown">
                        <el-dropdown-item command="cart" class="header-menu-cart">
                            购物车
                            <span v-if="cartList.length">{{ cartList.length }}</span>
                        </el-dropdown-item>
                        <el-dropdown-item command="exit">退出登录</el-dropdown-item>
                    </el-dropdown-menu>
                </el-dropdown>
            </div>
        </div>
        <router-view></router-view>
    </div>
</template>

<script>
    export default {
        computed: {
            cartList () {
                return this.$store.state.cartList;
            }
        },
        methods:{
            loginout(){
                this.$store.commit('clearUser');
                sessionStorage.removeItem('userinfo');
                console.log('退出成功');
                this.$router.push('/login');
            },
            handleUser(comm) {
                if (comm == "cart") {
                    this.$router.push('/cart')
                }
                else if (comm == "exit") {
                    this.$confirm("确认要退出吗？", "系统提示", {
                    confirmButtonText: "确认",
                    cancelButtonText: "取消",
                    type: "warning",
                    }).then(() => {
                        this.$store.commit('clearUser');
                        sessionStorage.removeItem('userinfo');
                        console.log('退出成功');
                        this.$router.push('/login');
                    });
                }
            },
        },
    }
</script>
