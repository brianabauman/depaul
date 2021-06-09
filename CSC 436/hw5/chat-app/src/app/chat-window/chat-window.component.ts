import { Component, OnInit, ChangeDetectionStrategy, ElementRef } from '@angular/core';
import { Observable } from 'rxjs';

import { Message } from '../message/message.model';
import { MessagesService } from '../message/messages.service';
import { Thread } from '../thread/thread.model';
import { ThreadsService } from '../thread/threads.service';
import { User } from '../user/user.model';
import { UsersService } from '../user/users.service';

@Component({
  selector: 'chat-window',
  changeDetection: ChangeDetectionStrategy.OnPush,
  templateUrl: './chat-window.component.html',
  styleUrls: ['./chat-window.component.css']
})
export class ChatWindow implements OnInit {
  messages: Observable<any>;
  currentThread: Thread;
  draftMessage: Message;
  currentUser: User;

  constructor(private messagesService: MessagesService,
              private threadsService: ThreadsService,
              private usersService: UsersService,
              private el: ElementRef) {
  }

  ngOnInit(): void {
    this.messages = this.threadsService.currentThreadMessages;
    this.draftMessage = new Message();
    this.threadsService.currentThread.subscribe(
      (thread: Thread) => {
        this.currentThread = thread;
      });
    this.usersService.currentUser.subscribe(
      (user: User) => {
        this.currentUser = user;
      });
    this.messages.subscribe(
      (messages: Array<Message>) => {
        setTimeout(() => {
          this.scrollToBottom();
        });
      });
  }

  sendMessage(): void {
    let m: Message = this.draftMessage;
    m.author = this.currentUser;
    m.thread = this.currentThread;
    m.isRead = true;
    this.messagesService.addMessage(m);
    this.draftMessage = new Message();
  }

  onEnter(event: any) {
    this.sendMessage();
    event.preventDefault();
  }

  scrollToBottom(): void {
    let scrollPane: any = this.el
      .nativeElement.querySelector('.msg-container-base');
    scrollPane.scrollTop = scrollPane.scrollHeight;
  }
}
