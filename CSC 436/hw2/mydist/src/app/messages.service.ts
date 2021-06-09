import { Injectable } from '@angular/core';
import { User } from '../models/user.model';
import { Message } from '../models/message.model';
import { Messages } from '../models/messages.model';

@Injectable({
  providedIn: 'root'
})
export class MessagesService {

  messages: Messages;

  constructor() { }

  createMessages(): Messages {
    var user1: User = new User();
    user1.name = "user1";
    var user2: User = new User();
    user2.name = "user2";

    var message1: Message = new Message();
    message1.text = "hello";
    message1.timestamp = "12:52:01 p.m."
    message1.from = user1;
    message1.to = user2;

    var message2: Message = new Message();
    message2.text = "hello";
    message2.timestamp = "12:52:41 p.m."
    message2.from = user2;
    message2.to = user1;

    var message3: Message = new Message();
    message3.text = "what's up?";
    message3.timestamp = "12:53:22 p.m."
    message3.from = user1;
    message3.to = user2;

    var message4: Message = new Message();
    message4.text = "not much";
    message4.timestamp = "12:53:59 p.m."
    message4.from = user2;
    message4.to = user1;

    var messages: Messages = new Messages();
    messages.messages = [message1, message2, message3, message4];

    return messages;
  }
}
