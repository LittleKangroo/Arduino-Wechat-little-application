//index.js
//获取应用实例
const app = getApp()

Page({
  send: function () {
    wx.request({
      url: 'http://api.heclouds.com/devices/505374882/datapoints?type=3',
      header: {
        'api-key': 'K8K5LOUaVpudnjNieA=FeSEOmAE='
      },
      data: '{"open":"123"}',
      method: 'POST',
      success(res) {
        console.log(res.data)
      }


    })
  },
  back: function () {
    wx.request({
      url: 'http://api.heclouds.com/devices/505374882/datapoints?type=3',
      header: {
        'api-key': 'K8K5LOUaVpudnjNieA=FeSEOmAE='
      },
      data: '{"open":"321"}',
      method: 'POST',
      success(res) {
        console.log(res.data)
      }


    })
  }
})
