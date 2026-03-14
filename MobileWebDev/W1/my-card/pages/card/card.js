// pages/card/card.js
Page({
  /**
   * 页面的初始数据
   * 所有数据均在此定义，WXML 中不硬编码任何文字
   */
  data: {
    // ========== 页面标题 ==========
    pageTitle: '个人名片',
    
    // ========== 基本信息 ==========
    // 头像URL（可替换为真实头像链接）
    avatarUrl: '/images/avater.jpg',
    
    // 姓名
    name: 'Octogen',
    
    // 专业年级
    majorGrade: '括号学院 2025级',
    
    // ========== 联系方式（对象数组）==========
    contacts: [
      {
        type: 'phone',
        label: '手机',
        value: '12345678910',
        icon: '/icons/phone.png'
      },
      {
        type: 'wechat',
        label: '微信',
        value: '1_wx',
        icon: '/icons/wechat.png'
      },
      {
        type: 'email',
        label: '邮箱',
        value: '1@qq.com',
        icon: '/icons/email.png'
      },
      {
        type: 'qq',
        label: 'QQ',
        value: '123456789',
        icon: '/icons/qq.png'
      }
    ],
    
    // ========== 技能标签 ==========
    skills: [
      'JavaScript',
      '微信小程序',
      'Vue.js',
      'Python',
      'Kotlin',
      'C++'
    ],
    
    // ========== 个人简介 ==========
    introduction: '学生，大学生，北京邮电大学大学生',
    
    // ========== 区块标题（用于WXML渲染）==========
    sectionTitles: {
      contact: '联系方式',
      skills: '技能标签',
      introduction: '个人简介'
    },
    
    // ========== 底部版权信息 ==========
    copyright: '© 2026 个人名片小程序'
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad(options) {
    // 页面加载时的逻辑
  },

  /**
   * 点击联系方式的处理函数
   * 根据不同的联系方式类型执行不同的操作
   */
  handleContactTap: function(e) {
    // 从事件对象中获取数据集
    const type = e.currentTarget.dataset.type;
    const value = e.currentTarget.dataset.value;
    
    switch(type) {
      case 'phone':
        // 手机号：调用拨打电话功能
        wx.makePhoneCall({
          phoneNumber: value,
          fail: (err) => {
            console.error('拨打电话失败', err);
          }
        });
        break;
        
      case 'wechat':
        // 微信号：复制到剪贴板
        wx.setClipboardData({
          data: value,
          success: () => {
            wx.showToast({
              title: '微信号已复制',
              icon: 'success'
            });
          }
        });
        break;
        
      case 'email':
        // 邮箱：复制到剪贴板
        wx.setClipboardData({
          data: value,
          success: () => {
            wx.showToast({
              title: '邮箱已复制',
              icon: 'success'
            });
          }
        });
        break;
        
      case 'qq':
        // QQ号：复制到剪贴板
        wx.setClipboardData({
          data: value,
          success: () => {
            wx.showToast({
              title: 'QQ号已复制',
              icon: 'success'
            });
          }
        });
        break;
        
      default:
        // 默认：复制内容
        wx.setClipboardData({
          data: value,
          success: () => {
            wx.showToast({
              title: '内容已复制',
              icon: 'success'
            });
          }
        });
    }
  },

  /**
   * 复制个人简介
   */
  copyIntroduction: function() {
    wx.setClipboardData({
      data: this.data.introduction,
      success: () => {
        wx.showToast({
          title: '简介已复制',
          icon: 'success'
        });
      }
    });
  },

  /**
   * 分享功能
   */
  onShareAppMessage: function() {
    return {
      title: this.data.name + '的名片',
      path: '/pages/card/card',
      imageUrl: this.data.avatarUrl
    };
  }
});
