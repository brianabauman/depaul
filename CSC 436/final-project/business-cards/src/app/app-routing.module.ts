import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';

import { LoginComponent } from './login/login.component';
import { EditBusinessCardComponent } from './edit-business-card/edit-business-card.component';
import { AddBusinessCardComponent } from './add-business-card/add-business-card.component';
import { AuthGuardService } from './auth-guard.service';
import { WebcamScreenshotComponent } from './webcam-screenshot/webcam-screenshot.component';
import { BusinessCardListComponent } from './business-card-list/business-card-list.component';

const routes: Routes = [
  { path: '', redirectTo: 'home', pathMatch: 'full' },
  { path: 'login', component: LoginComponent }, 
  { path: 'home', component: BusinessCardListComponent, canActivate: [ AuthGuardService ] },
  { path: 'edit/:userID/:cardID', component: EditBusinessCardComponent, canActivate: [ AuthGuardService ] },
  { path: 'add', component: AddBusinessCardComponent, canActivate: [ AuthGuardService ] },
  { path: 'add/:text', component: AddBusinessCardComponent, canActivate: [ AuthGuardService ] },
  { path: 'screenshot', component: WebcamScreenshotComponent, canActivate: [ AuthGuardService ] },
  { path: '**', component: LoginComponent }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
