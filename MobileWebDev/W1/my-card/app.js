// app.js
// 小程序入口文件

App({
  /**
   * 小程序全局数据
   */
  globalData: {
    userInfo: null,
    // 可以在这里存放全局共享的数据
  },

  /**
   * 小程序初始化完成时执行
   */
  onLaunch() {
    console.log('小程序启动');
    
    // 检查更新
    this.checkUpdate();
  },

  /**
   * 检查小程序更新
   */
  checkUpdate() {
    const updateManager = wx.getUpdateManager();
    
    updateManager.onCheckForUpdate(function(res) {
      console.log('是否有新版本：', res.hasUpdate);
    });
    
    updateManager.onUpdateReady(function() {
      wx.showModal({
        title: '更新提示',
        content: '新版本已经准备好，是否重启应用？',
        success: function(res) {
          if (res.confirm) {
            updateManager.applyUpdate();
          }
        }
      });
    });
    
    updateManager.onUpdateFailed(function() {
      console.log('新版本下载失败');
    });
  }
});
