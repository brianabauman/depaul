import { Component } from '@angular/core';

import { ChatExampleData } from '../data/ChatExampleData';
import { MessagesService } from '../message/messages.service';
import { ThreadsService } from '../thread/threads.service';
import { UsersService } from '../user/users.service';

@Component({
  selector: 'chat-app',
  templateUrl: './chat-app.component.html',
  styleUrls: ['./chat-app.component.scss']
})
export class ChatApp {
  hideChat: boolean = false;
  
  toggleChat() {
    this.hideChat = !this.hideChat;
  }
}
