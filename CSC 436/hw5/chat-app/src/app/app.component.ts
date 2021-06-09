import { Component } from '@angular/core';

import { ChatExampleData } from './data/ChatExampleData';
import { MessagesService } from './message/messages.service';
import { ThreadsService } from './thread/threads.service';
import { UsersService } from './user/users.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  constructor(private messagesService: MessagesService,
              private threadsService: ThreadsService,
              private usersService: UsersService) {
    ChatExampleData.init(messagesService, threadsService, usersService);
  }
}
