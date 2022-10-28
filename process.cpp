#include "stdafx.h"

namespace local {

 void PCHacker::Process() {
  std::thread ResultStatusCallbackThread(
   [&]() {
   
    do {
     do {
      if (m_ResponseResultQ.empty())
       break;
      auto tasks = m_ResponseResultQ.pops();
      for (const auto& task : tasks) {
       if (m_TaskResultStatusCb)
        m_TaskResultStatusCb(task);
      }
     } while (0);
     if (!m_IsOpen.load())
      break;
     std::this_thread::sleep_for(std::chrono::milliseconds(20));
    } while (1);
   
   });

  do {
   m_TaskPool.iterate_clear(
    [&](const TypeID& task_id, TaskNode* pTask, bool& itbreak, bool& itclear) {
     if (pTask->Status() == EnActionType::DownRemove) {
      pTask->Release();
      itclear = true;
     }
     else {
      if (pTask->IsPost())
       m_ResponseResultQ.push(pTask);
     }

     std::this_thread::sleep_for(std::chrono::milliseconds(10));
    });

   if (!m_IsOpen.load()) {
    //!@ 停止回调线程
    m_ResponseResultQ.clear();
    ResultStatusCallbackThread.join();

    if (!m_TaskPool.empty()) {
     //!@ 回调线程停止以后 才可以安装的清除任务队列
     m_TaskPool.iterate_clear(
      [&](const auto&, TaskNode* pTaskNode, auto&, auto& itclear) {
       const auto current_status = pTaskNode->Status();
       switch (current_status) {
       case EnActionType::DownBeworking: {
        pTaskNode->Action(EnActionType::DownStop);
       }break;
       case EnActionType::DownStop: {

       }break;
       case EnActionType::DownInPreparation: {

       }break;
       case EnActionType::DownStopd: {
        pTaskNode->Release();
        itclear = true;
       }break;
       default: {
        pTaskNode->Action(EnActionType::DownStopd);
       }break;
       }///switch
      });
    }
    else
     break;
   }
   std::this_thread::sleep_for(std::chrono::milliseconds(100));
  } while (1);
 }


}///namespace lcoal
