import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class MyServiceService {

  constructor() { }

  likeImage(liked: boolean): boolean {
      return !liked;
  }
}
