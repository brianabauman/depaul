import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { MyImageComponent } from './my-image/my-image.component';
import { MyButtonComponent } from './my-button/my-button.component';

@NgModule({
  declarations: [
    AppComponent,
    MyImageComponent,
    MyButtonComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
