import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { AngularFireModule } from '@angular/fire';
import { AngularFireAuthModule } from '@angular/fire/auth'
import { RouterModule, Routes } from '@angular/router';
import { platformBrowserDynamic } from '@angular/platform-browser-dynamic';
import { FromNowPipe } from './pipes/from-now.pipe';

import { AppComponent } from './app.component';
import { ChatThreads } from './chat-threads/chat-threads.component';
import { ChatThread } from './chat-thread/chat-thread.component';
import { ChatWindow } from './chat-window/chat-window.component';
import { ChatMessage } from './chat-message/chat-message.component';
import { ChatNavBar } from './chat-nav-bar/nav-bar.component';
import { ChatLogin } from './chat-login/chat-login.component';
import { ChatApp } from './chat-app/chat-app.component';

import { MessagesService } from './message/messages.service';
import { ThreadsService } from './thread/threads.service';
import { UsersService } from './user/users.service';
import { AuthService } from './auth.service'
import { AuthGuardService } from './auth-guard.service';

import { environment } from '../environments/environment';

export const routes: Routes = [
  { path: '', redirectTo: 'home', pathMatch: 'full' },
  { path: 'home', component: ChatApp, canActivate: [ AuthGuardService ] },
  { path: 'login', component: ChatLogin },
  { path: '**', component: ChatLogin }
];

@NgModule({
  declarations: [
    AppComponent,
    ChatNavBar,
    ChatThreads,
    ChatThread,
    ChatWindow,
    ChatMessage,
    ChatThreads,
    ChatThread,
    ChatWindow,
    ChatMessage,
    ChatNavBar,
    FromNowPipe,
    ChatLogin,
    ChatApp
  ],
  imports: [
    BrowserModule,
    FormsModule,
    ReactiveFormsModule,
    RouterModule.forRoot(routes),
    AngularFireModule.initializeApp(environment.firebaseConfig, 'my-app-name'), // imports firebase/app needed for everything
    AngularFireAuthModule
  ],
  providers: [
    MessagesService, ThreadsService, UsersService, AuthService, AuthGuardService
  ],
  bootstrap: [ AppComponent ]
})
export class AppModule { }

platformBrowserDynamic().bootstrapModule(AppModule);