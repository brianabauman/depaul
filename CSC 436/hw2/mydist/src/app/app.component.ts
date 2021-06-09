import { Component } from '@angular/core';
import { Message } from '../models/message.model'
import { Messages } from '../models/messages.model'
import { MessagesService } from './messages.service'

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})

export class AppComponent {
  title = 'mydist';
  messages: Messages;

  constructor(private messageService: MessagesService) {
      this.messages = this.messageService.createMessages();
  }
}
