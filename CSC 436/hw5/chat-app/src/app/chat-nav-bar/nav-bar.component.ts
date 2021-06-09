import { Component, OnInit } from '@angular/core';
import { combineLatest } from 'rxjs';
import * as _ from 'lodash';

import { Message } from '../message/message.model';
import { MessagesService } from '../message/messages.service';
import { Thread } from '../thread/thread.model';
import { ThreadsService } from '../thread/threads.service';
import { AuthService } from '../auth.service';
import { Router } from '@angular/router';

@Component({
  selector: 'nav-bar',
  templateUrl: './nav-bar.component.html',
  styleUrls: ['./nav-bar.component.css']
})
export class ChatNavBar implements OnInit {
  unreadMessagesCount: number;

  constructor(private messagesService: MessagesService,
              private threadsService: ThreadsService,
              private authService: AuthService,
              private router: Router) { }

    ngOnInit(): void {
        combineLatest(
          this.messagesService.messages,
          this.threadsService.currentThread,
          (messages: Message[], currentThread: Thread) =>
            [currentThread, messages] )
        .subscribe(([currentThread, messages]: [Thread, Message[]]) => {
          this.unreadMessagesCount =
            _.reduce(
              messages,
              (sum: number, m: Message) => {
                const messageIsInCurrentThread: boolean = m.thread &&
                  currentThread &&
                  (currentThread.id === m.thread.id);
                // note: in a "real" app you should also exclude
                // messages that were authored by the current user b/c they've
                // already been "read"
                if (m && !m.isRead && !messageIsInCurrentThread) {
                  sum = sum + 1;
                }
                return sum;
              },
              0);
        });
    }

    logout() {
      this.authService.logout();
      this.router.navigate(['/login']);
    }
}
