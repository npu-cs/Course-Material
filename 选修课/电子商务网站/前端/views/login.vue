<template>
  <div class="login-container">
    <div class="login-win">
      <div class="login-body" v-loading="loading">
        <h1 class="login-title">用户登录</h1>
        <el-form
          :model="loginForm"
          status-icon
          :rules="rules"
          ref="loginForm"
          label-width="100px"
          class="demo-loginForm"
        >
          <el-form-item label="用户名：" prop="username">
            <el-input
              prefix-icon="el-icon-user"
              style="width: 250px"
              type="text"
              v-model="loginForm.username"
              autocomplete="off"
            ></el-input>
          </el-form-item>
          <el-form-item label="密 码：" prop="password">
            <el-input
              prefix-icon="el-icon-menu"
              style="width: 250px"
              show-password
              type="password"
              v-model="loginForm.password"
              autocomplete="off"
            ></el-input>
          </el-form-item>
          <el-form-item>
            <el-button 
            style="margin-top: 25px; width: 70%; background-color: #668ccc"
            type="primary" @click="submitForm('loginForm')"
              >登录</el-button
            >
          </el-form-item>
        </el-form>
      </div>
    </div>
  </div>
</template>

<script>
import jwt from 'jwt-decode';
let request = require("../request.js");

export default {
  data() {
    var validateUsername = (rule, value, callback) => {
      if (value === "") {
        callback(new Error("请输入用户账号"));
      } else {
        callback();
      }
    };
    var validatePassword = (rule, value, callback) => {
      if (value === "") {
        callback(new Error("请输入用户密码"));
      } else if (value.length < 8 || value.length > 13) {
        callback(new Error("长度必须在8-12之内!"));
      } else {
        callback();
      }
    };
    return {
      loading: false,
      loginForm: {
        username: "",
        password: "",
      },
      rules: {
        username: [{ validator: validateUsername, trigger: "blur" }],
        password: [{ validator: validatePassword, trigger: "blur" }],
      },
    };
  },
  methods: {
    submitForm(formName) {
      this.$refs[formName].validate((valid) => {
        if (valid) {
          request.SetSrvHost();
          request.get_login_token({
            user:this.loginForm.username,
            pwd:this.loginForm.password
          })
          .then(res=>{
            // console.log(jwt(res.data.token));
            let obj = {
                token:res.data.token,
                username:jwt(res.data.token).user
            }
            this.$store.commit('setUser',obj)
            // 数据持久化
            sessionStorage.setItem('userinfo',JSON.stringify(obj))
            this.$router.push('/list')
          })


        } else {
          console.log("校验失败");
          return false;
        }
      });
    },
  },
};
</script>
 
<style>
.login-container {
  background-image: url("../bg.jpg");
  background-size: cover;
  position: fixed;
  left: 0;
  top: 0;
  bottom: 0;
  right: 0;
}
.login-win {
  position: absolute;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);
  width: 400px;
  height: 300px;
  padding: 15px 25px;
  border-radius: 5px;
  background-color: #fff;
}
.login-body {
  width: 100%;
}
.login-title {
  text-align: center;
  font-size: 20px;
  font-weight: bold;
  color: #668ccc;
  margin-bottom: 45px;
  margin-top: 15px;
}
</style>
