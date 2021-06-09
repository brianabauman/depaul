import { Component, OnInit, ChangeDetectionStrategy } from '@angular/core';
import { Observable } from 'rxjs';

import { ThreadsService } from '../thread/threads.service';

@Component({
  selector: 'chat-threads',
  changeDetection: ChangeDetectionStrategy.OnPush,
  templateUrl: './chat-threads.component.html',
  styleUrls: ['./chat-threads.component.css']
})
export class ChatThreads {
  threads: Observable<any>;

  constructor(private threadsService: ThreadsService) {
    this.threads  = threadsService.orderedThreads;
  }
}
